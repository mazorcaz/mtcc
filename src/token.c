// token.c

#include <stdlib.h>

#include "token.h"

void token_free(struct token *token)
{
	switch (token->type) {
	case TOKEN_IDENT:
		free(token->types.ident.str);
	}
}
