// dstr.h

#ifndef MTCC_DSTR_H
#define MTCC_DSTR_H

#include <stddef.h>

struct dstr {
	size_t len; // length of used portion of buffer
	size_t sz; // actual size of buffer
	char* buf;
};

int dstr_init(struct dstr* dstr); // 0 on fail
void dstr_free(struct dstr* dstr);

int dstr_add(struct dstr* dstr, char c);

#endif
