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
#define LEXER_MODE_LINECOMMENT 4
#define LEXER_MODE_INLINECOMMENT 5
#define LEXER_MODE_INLINECOMMENT_STAR 6

#define LEXER_MODE_OP_PLUS 100
#define LEXER_MODE_OP_MINUS 101
#define LEXER_MODE_OP_PLUSPLUS 102
#define LEXER_MODE_OP_MINUSMINUS 103
#define LEXER_MODE_OP_STAR 104
#define LEXER_MODE_OP_SLASH 105
#define LEXER_MODE_OP_ARROW 106
#define LEXER_MODE_OP_OPENBRACE 107
#define LEXER_MODE_OP_CLOSEBRACE 108
#define LEXER_MODE_OP_OPENPAR 109
#define LEXER_MODE_OP_CLOSEPAR 110
#define LEXER_MODE_OP_OPENBRACKET 111
#define LEXER_MODE_OP_CLOSEBRACKET 112

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
