/* main.c */

#include <unistd.h>

#include "string.h"
#include "alloc.h"

int main()
{
	struct arena arena;
	char *dat, *str, *dst;

	arena_init(&arena);

	dat = arena_alloc(&arena, 64);

	str = "Hello world\n";
	dst = dat;
	while (*str) {
		*dst++ = *str++;
	}
	*dst = 0;

	write(1, dat, dst - dat);
	
	arena_free(&arena);

	_exit(0);
}
