#!/bin/sh

CC=tcc
CFLAGS="-g"

mkdir -p bin/
$CC $CFLAGS src/*.c -o bin/mtcc
