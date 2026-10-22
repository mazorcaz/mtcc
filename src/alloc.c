/* alloc.c */

#include "alloc.h"
#include "string.h"

struct heapseg *freelist;

struct heapseg *allocseg()
{
	struct heapseg *old;

	if (freelist == 0) {
		freelist = sbrk(HEAPSEGSZ);
		if (freelist == (void *)-1) {
			WRCONST(2, "allocseg: sbrk failed\n");
			return 0;
		}
		freelist->next = 0;
	}

	old = freelist;
	freelist = freelist->next;
	return old;
}

void freesegs(struct heapseg *segs)
{
	struct heapseg *old;

	if (segs == 0) return;

	old = freelist;
	freelist = segs;
	while (segs->next) segs = segs->next;
	segs->next = old;
}

void arena_init(struct arena *arena)
{
	arena->seglist = 0;
	arena->idx = 0;
}

void arena_free(struct arena *arena)
{
	freesegs(arena->seglist);
	arena->seglist = 0;
}

void *arena_alloc(struct arena *arena, int sz)
{
	void *ptr;

	if (sz > HEAPSEGSZ - sizeof(struct heapseg)) {
		WRCONST(2, "arena_alloc: alloc exceeds heapseg size\n");
		return 0;
	}

	arena->idx = (arena->idx + 7) & -8;
	if (!arena->seglist || arena->idx + sz > HEAPSEGSZ) {
		arena->idx = sizeof(struct heapseg);

		struct heapseg *newseg = allocseg();
		if (!newseg) return 0;

		newseg->next = arena->seglist;
		arena->seglist = newseg;
	}

	ptr = (void *)((char *)arena->seglist + arena->idx);
	arena->idx += sz;

	return ptr;
}
