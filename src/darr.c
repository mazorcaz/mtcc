// darr.c

#include <stdio.h>
#include <stdlib.h>

#include "darr.h"

int darr_init(struct darr *darr)
{
	darr->len = 0;
	darr->sz = 16;
	darr->buf = malloc(sizeof(void*) * darr->sz);
	if (!darr->buf) {
		fprintf(stderr, "darr_init: malloc failed\n");
		return 0;
	}
	return 1;
}

void darr_free(struct darr *darr)
{
	free(darr->buf);
	darr->buf = NULL;
}

int darr_add(struct darr *darr, void* v)
{
	if (darr->len >= darr->sz) {
		do {
			darr->sz <<= 1;
		} while (darr->len >= darr->sz);
		void **newbuf = malloc(sizeof(void*) * darr->sz);
		if (!newbuf) {
			fprintf(stderr, "darr_add: malloc failed\n");
			return 0;
		}
		darr->buf = newbuf;
	}
	darr->buf[darr->len++] = v;
	return 1;
}
