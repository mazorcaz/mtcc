// lexer.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
	}
	darr_free(&lexer->tokens);
	dstr_free(&lexer->str);
}

int lexer_parse(struct lexer* lexer, FILE *file)
{
	int line = 1;

	int c;
	while (1) {
		c = fgetc(file);
	reswitch:
		switch (lexer->mode) {
		case LEXER_MODE_START:
			if (c == EOF) {
				return 1;
			} if (isspace(c)) {
				goto skipchar;
			} else if (isalpha(c) || c == '_') {
				lexer->mode = LEXER_MODE_IDENT;
				goto tokenstart;
			} else if (isdigit(c)) {
				lexer->mode = LEXER_MODE_DIGIT;
				goto tokenstart;
			} else if (c == '_' || c == '*') {
				lexer->mode = LEXER_MODE_OP;
				goto tokenstart;
			} else {
				fprintf(stderr, "unexpected character '%c' (0x%02x) on line %i\n", c, c, line);
				return 0;
			}
		case LEXER_MODE_IDENT:
			if ((lexer->str.len == 0 && (isalpha(c) || c == '_')) || (isalnum(c) || c == '_')) {
				goto nextchar;
			} else {
				goto tokenend;
			}
		case LEXER_MODE_DIGIT:
			if (isdigit(c)) {
				goto nextchar;
			} else {
				goto tokenend;
			}
		case LEXER_MODE_OP:
			if (c == '+') {
				lexer->token->type = TOKEN_OP;
				lexer->token->types.op
			}
		}
		return 0;

	tokenstart:
		lexer->token = malloc(sizeof(struct token));
		if (!lexer->token) {
			fprintf(stderr, "lexer_parse: malloc failed\n");
			return 0;
		}
		goto reswitch;

	tokenend:
		if (!darr_add(&lexer->tokens, lexer->token)) return 0;
		lexer->mode = LEXER_MODE_START;
		goto reswitch;

	nextchar:
		if (!dstr_add(&lexer->str, c)) return 0;
	skipchar:
		if (c == '\n') line++;
	}
}
