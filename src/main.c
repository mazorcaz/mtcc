// main.c

#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main()
{
	struct lexer lexer;
	if (!lexer_init(&lexer)) return -1;
	if (!lexer_parse(&lexer, stdin)) return -1;

	printf("len is %i\n", lexer.tokens.len);
	for (int i=0; i<lexer.tokens.len; i++) {
		struct token *token = lexer.tokens.buf[i];
		if (token->type == TOKEN_IDENT) {
			printf("IDENT %s\n", token->types.ident.str);
		} else if (token->type == TOKEN_NUM) {
			printf("NUM %i\n", token->types.num.value);
		} else if (token->type == TOKEN_OP) {
			switch (token->types.op.type) {
			case TOKEN_OP_PLUS:
				printf("OP +\n");
				break;
			case TOKEN_OP_MINUS:
				printf("OP -\n");
				break;
			case TOKEN_OP_PLUSPLUS:
				printf("OP ++\n");
				break;
			case TOKEN_OP_MINUSMINUS:
				printf("OP --\n");
				break;
			}
		}
	}

	lexer_free(&lexer);

	return 0;
}
