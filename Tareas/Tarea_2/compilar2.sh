#!/bin/sh
as --32  $1.s -o $1.o
as --32  $2.s -o $2.o
ld -m elf_i386 $1.o $2.o -o $3
./$3
echo $?