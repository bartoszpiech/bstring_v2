#!/bin/sh

CC=gcc
CFLAGS="-Wall -pedantic -std=c11 -g"
INC=bstring.c
OBJ=bstring.o
SRC=bstring_tests.c
BIN=tests

$CC $CFLAGS -c $INC -o $OBJ && $CC $CFLAGS $SRC $OBJ -o $BIN && ./$BIN
