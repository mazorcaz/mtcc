// lexer.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

int lexer_init(struct lexer *lexer)
{
	if (!darr_init(&lexer->tokens)) return 0;
	if (!dstr_init(&lexer->str)) return 0;
	lexer->mode = LEXER_MODE_START;
	return 1;
}

void lexer_free(struct lexer *lexer)
{
	for (int i=0; i<lexer->tokens.len; i++) {
		token_free(lexer->tokens.buf[i]);
		free(lexer->tokens.buf[i]);
	}
	darr_free(&lexer->tokens);
	dstr_free(&lexer->str);
}

int lexer_parse(struct lexer *lexer, FILE *file)
{
	int line = 1;

	int c;
	while (1) {
		c = fgetc(file);
	reswitch:
		switch (lexer->mode) {
		case LEXER_MODE_START:
			if (c == EOF) return 1;
			
			if (isspace(c)) goto skipchar;

			if (isalpha(c) || c == '_') {
				lexer->mode = LEXER_MODE_IDENT;
			} else if (isdigit(c)) {
				lexer->mode = LEXER_MODE_DIGIT;
			} else if (c == '+') {
				lexer->mode = LEXER_MODE_OP_PLUS;
			} else if (c == '-') {
				lexer->mode = LEXER_MODE_OP_MINUS;
			} else if (c == '*') {
				lexer->mode = LEXER_MODE_OP_STAR;
			} else if (c == '/') {
				lexer->mode = LEXER_MODE_OP_SLASH;
			} else if (c == '{') {
				lexer->mode = LEXER_MODE_OP_OPENBRACE;
			} else if (c == '}') {
				lexer->mode = LEXER_MODE_OP_CLOSEBRACE;
			} else if (c == '(') {
				lexer->mode = LEXER_MODE_OP_OPENPAR;
			} else if (c == ')') {
				lexer->mode = LEXER_MODE_OP_CLOSEPAR;
			} else if (c == '[') {
				lexer->mode = LEXER_MODE_OP_OPENBRACKET;
			} else if (c == ']') {
				lexer->mode = LEXER_MODE_OP_CLOSEBRACKET;
			} else if (c == '.') {
				lexer->mode = LEXER_MODE_OP_DOT;
			} else if (c == ';') {
				lexer->mode = LEXER_MODE_OP_SEMICOLON;
			} else {
				fprintf(stderr, "unexpected character '%c' (0x%02x) on line %i\n", c, c, line);
				return 0;
			}

			goto tokenstart;
		case LEXER_MODE_LINECOMMENT:
			if (c == '\n') {
				lexer->mode = LEXER_MODE_START;
				goto skipchar;
			}
			goto skipchar;
		case LEXER_MODE_INLINECOMMENT:
			if (c == '*') {
				lexer->mode = LEXER_MODE_INLINECOMMENT_STAR;
				goto skipchar;
			}
			goto skipchar;
		case LEXER_MODE_INLINECOMMENT_STAR:
			if (c == '/') {
				lexer->mode = LEXER_MODE_START;
				goto skipchar;
			}
			goto skipchar;
		case LEXER_MODE_IDENT:
			if (isalnum(c) || c == '_') {
				goto nextchar;
			} else {
				if (strcmp(lexer->str.buf, "int") == 0) {
					lexer->token->type = TOKEN_KEYWORD;
					lexer->token->types.keyword.type = TOKEN_KEYWORD_INT;
					goto tokenend;
				} else if (strcmp(lexer->str.buf, "char") == 0) {
					lexer->token->type = TOKEN_KEYWORD;
					lexer->token->types.keyword.type = TOKEN_KEYWORD_CHAR;
					goto tokenend;
				} else {
					lexer->token->type = TOKEN_IDENT;
					lexer->token->types.ident.str = lexer->str.buf;
					if (!dstr_init(&lexer->str)) return 0;
					goto tokenend;
				}
			}
		case LEXER_MODE_DIGIT:
			if (isdigit(c)) {
				goto nextchar;
			} else {
				char *endptr;
				lexer->token->type = TOKEN_NUM;
				lexer->token->types.num.value = strtol(lexer->str.buf, &endptr, 10);
				goto tokenend;
			}
		case LEXER_MODE_OP_PLUS:
			if (c == '+') {
				lexer->mode = LEXER_MODE_OP_PLUSPLUS;
				goto nextchar;
			} else {
				lexer->token->type = TOKEN_OP;
				lexer->token->types.op.type = TOKEN_OP_PLUS;
				goto tokenend;
			}
		case LEXER_MODE_OP_MINUS:
			if (c == '-') {
				lexer->mode = LEXER_MODE_OP_MINUSMINUS;
				goto nextchar;
			} else if (c == '>') {
				lexer->mode = LEXER_MODE_OP_ARROW;
				goto nextchar;
			} else {
				lexer->token->type = TOKEN_OP;
				lexer->token->types.op.type = TOKEN_OP_MINUS;
				goto tokenend;
			}
		case LEXER_MODE_OP_PLUSPLUS:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_PLUSPLUS;
			goto tokenend;
		case LEXER_MODE_OP_MINUSMINUS:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_MINUSMINUS;
			goto tokenend;
		case LEXER_MODE_OP_STAR:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_STAR;
			goto tokenend;
		case LEXER_MODE_OP_SLASH:
			if (c == '/') {
				lexer->mode = LEXER_MODE_LINECOMMENT;
				goto skipchar;
			} else if (c == '*') {
				lexer->mode = LEXER_MODE_INLINECOMMENT;
				goto skipchar;
			}
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_SLASH;
			goto tokenend;
		case LEXER_MODE_OP_ARROW:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_ARROW;
			goto tokenend;
		case LEXER_MODE_OP_OPENBRACE:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_OPENBRACE;
			goto tokenend;
		case LEXER_MODE_OP_CLOSEBRACE:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_CLOSEBRACE;
			goto tokenend;
		case LEXER_MODE_OP_OPENPAR:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_OPENPAR;
			goto tokenend;
		case LEXER_MODE_OP_CLOSEPAR:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_CLOSEPAR;
			goto tokenend;
		case LEXER_MODE_OP_OPENBRACKET:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_OPENBRACKET;
			goto tokenend;
		case LEXER_MODE_OP_CLOSEBRACKET:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_CLOSEBRACKET;
			goto tokenend;
		case LEXER_MODE_OP_DOT:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_DOT;
			goto tokenend;
		case LEXER_MODE_OP_SEMICOLON:
			lexer->token->type = TOKEN_OP;
			lexer->token->types.op.type = TOKEN_OP_SEMICOLON;
			goto tokenend;
		}
		return 0;

	tokenend:
		if (!darr_add(&lexer->tokens, lexer->token)) return 0;
		lexer->mode = LEXER_MODE_START;
		goto reswitch;

	tokenstart:
		lexer->str.len = 0;
		lexer->token = malloc(sizeof(struct token));
		if (!lexer->token) {
			fprintf(stderr, "lexer_parse: malloc failed\n");
			return 0;
		}
	nextchar:
		if (!dstr_add(&lexer->str, c)) return 0;
	skipchar:
		if (c == '\n') line++;
	}
}
