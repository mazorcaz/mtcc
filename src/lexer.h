// lexer.h

#ifndef MTCC_LEXER_H
#define MTCC_LEXER_H

#include <stdio.h>

#include "dstr.h"
#include "darr.h"

#define LEXER_MODE_START 1
#define LEXER_MODE_IDENT 2

struct lexer {
	int mode;
	struct darr tokens;
	struct dstr str;
};

int lexer_init(struct lexer *lexer);
void lexer_free(struct lexer *lexer);

// 0 on failure to parse tokens
int lexer_parse(struct lexer *lexer, FILE *file);

#endif
