#!/bin/sh

CC=tcc
CFLAGS="-std=c11 -pedantic -fno-strict-aliasing"

mkdir -p bin/
$CC $CFLAGS src/*.c -o bin/mtcc
strip bin/mtcc
ls -lh bin/mtcc
