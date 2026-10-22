/* string.h */

#ifndef STRING_H
#define STRING_H

#include <unistd.h>

#define WRCONST(f, s) write(f, s, sizeof(s)-1)

#endif
