// darr.h

#ifndef MTCC_DARR_H
#define MTCC_DARR_H

#include <stddef.h>

struct darr {
	size_t len;
	size_t sz;
	void **buf;
};

int darr_init(struct darr *darr);
void darr_free(struct darr *darr);

int darr_add(struct darr *darr, void* v);

#endif
