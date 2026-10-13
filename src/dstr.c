// dstr.c

#include <stdio.h>
#include <stdlib.h>

#include "dstr.h"

int dstr_init(struct dstr* dstr)
{
	dstr->len = 0;
	dstr->sz = 16;
	dstr->buf = malloc(dstr->sz);
	if (!dstr->buf) {
		fprintf(stderr, "dstr_init: malloc failed\n");
		return 0;
	}
	return 1;
}

void dstr_free(struct dstr* dstr)
{
	free(dstr->buf);
	dstr->buf = NULL;
}
