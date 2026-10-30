// token.h

#ifndef MTCC_TOKEN_H
#define MTCC_TOKEN_H

#define TOKEN_IDENT 1
#define TOKEN_KEYWORD 2
#define TOKEN_NUM 3
#define TOKEN_OP 4

#define TOKEN_KEYWORD_INT 1
#define TOKEN_KEYWORD_CHAR 2
#define TOKEN_KEYWORD_FLOAT 3
#define TOKEN_KEYWORD_DOUBLE 4
#define TOKEN_KEYWORD_SHORT 5
#define TOKEN_KEYWORD_LONG 6
#define TOKEN_KEYWORD_RETURN 7

#define TOKEN_OP_PLUS 1
#define TOKEN_OP_MINUS 2
#define TOKEN_OP_PLUSPLUS 3
#define TOKEN_OP_MINUSMINUS 4
#define TOKEN_OP_STAR 5
#define TOKEN_OP_SLASH 6
#define TOKEN_OP_ARROW 7
#define TOKEN_OP_OPENBRACE 8
#define TOKEN_OP_CLOSEBRACE 9
#define TOKEN_OP_OPENPAR 10
#define TOKEN_OP_CLOSEPAR 11
#define TOKEN_OP_OPENBRACKET 12
#define TOKEN_OP_CLOSEBRACKET 13
#define TOKEN_OP_DOT 14
#define TOKEN_OP_SEMICOLON 15

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
