// dstr.c

#include <stdio.h>
#include <stdlib.h>

#include "dstr.h"

int dstr_init(struct dstr *dstr)
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

void dstr_free(struct dstr *dstr)
{
	free(dstr->buf);
	dstr->buf = NULL;
}

int dstr_add(struct dstr *dstr, char c)
{
	if (dstr->len >= dstr->sz) {
		do {
			dstr->sz <<= 1;
		} while (dstr->len >= dstr->sz);
		char *newbuf = realloc(dstr->buf, dstr->sz);
		if (!newbuf) {
			fprintf(stderr, "dstr_init: malloc failed\n");
			return 0;
		}
		dstr->buf = newbuf;
	}
	dstr->buf[dstr->len++] = c;
	return 1;
}
