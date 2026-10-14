// lexer.h

#ifndef MTCC_LEXER_H
#define MTCC_LEXER_H

#include <stdio.h>

#include "dstr.h"
#include "darr.h"
#include "token.h"

#define LEXER_MODE_START 1
#define LEXER_MODE_IDENT 2
#define LEXER_MODE_DIGIT 3
#define LEXER_MODE_OP 4
#define LEXER_MODE_OP_PLUS 5
#define LEXER_MODE_OP_MINUS 6
#define LEXER_MODE_OP_PLUSPLUS 7
#define LEXER_MODE_OP_MINUSMINUS 8
#define LEXER_MODE_OP_STAR 9
#define LEXER_MODE_OP_SLASH 10
#define LEXER_MODE_HASH 11

struct lexer {
	int mode;
	struct darr tokens;
	struct dstr str;

	struct token *token;
};

int lexer_init(struct lexer *lexer);
void lexer_free(struct lexer *lexer);

// 0 on failure to parse tokens
int lexer_parse(struct lexer *lexer, FILE *file);

#endif
