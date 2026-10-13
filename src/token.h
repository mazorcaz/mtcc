// token.h

#ifndef MTCC_TOKEN_H
#define MTCC_TOKEN_H

#define TOKEN_IDENT 1
#define TOKEN_KEYWORD 2
#define TOKEN_NUM 3
#define TOKEN_OP 4

#define TOKEN_KEYWORD_INT 1
#define TOKEN_KEYWORD_CHAR 2

#define TOKEN_OP_PLUS 1
#define TOKEN_OP_MINUS 2

struct token_ident {
	char *str;
};

struct token_keyword {
	int type;
};

struct token_num {
	int value;
};

struct token_op {
	int type;
};

struct token {
	int type;
	union {
		struct token_ident ident;
		struct token_keyword keyword;
		struct token_num num;
		struct token_op op;
	} types;
};

void token_free(struct token *token);

#endif
