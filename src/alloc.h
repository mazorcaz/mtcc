/* alloc.h */

#ifndef ALLOC_H
#define ALLOC_H

#define HEAPSEGSZ 4096

struct heapseg {
	void *next;
};

struct heapseg *allocseg();
void freesegs(struct heapseg *segs);

struct arena {
	struct heapseg *seglist;
	int idx; /* index of free space in 1st segment FROM START */
};

void arena_init(struct arena *arena); /* 0 is success */
void arena_free(struct arena *arena);

void *arena_alloc(struct arena *arena, int sz);

#endif
