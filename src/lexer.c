// lexer.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int lexer_init(struct lexer *lexer)
{
	if (!darr_init(&lexer->tokens)) return 0;
	lexer->mode = LEXER_MODE_START;
	return 1;
}

void lexer_free(struct lexer *lexer)
{
	for (int i=0; i<lexer->tokens.len; i++) {
		free(lexer->tokens.buf[i]);
	}
	darr_free(&lexer->tokens);
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
			} else {
				fprintf(stderr, "unexpected character '%c' (0x%02x) on line %i\n", c, c, line);
				return 0;
			}
		case LEXER_MODE_IDENT:
			if (isalnum(c) || c == '_') {
				goto nextchar;
			} else {
				goto tokenend;
			}
		}
		return 0;

	tokenend:
		if (!darr_add(&lexer->tokens, lexer->str.buf)) return 0;
		lexer->mode = LEXER_MODE_START;
		goto reswitch;

	tokenstart:
		if (!dstr_init(&lexer->str)) return 0;
	nextchar:
		if (!dstr_add(&lexer->str, c)) return 0;
	skipchar:
		if (c == '\n') line++;
	}
}
