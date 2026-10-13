// main.c

#include <stdio.h>

#include "lexer.h"

int main()
{
	struct lexer lexer;
	if (!lexer_init(&lexer)) return -1;
	if (!lexer_parse(&lexer, stdin)) return -1;

	printf("len is %i\n", lexer.tokens.len);
	for (int i=0; i<lexer.tokens.len; i++) {
		printf("%s\n", lexer.tokens.buf[i]);
	}

	lexer_free(&lexer);

	return 0;
}
