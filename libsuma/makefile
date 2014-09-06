# Copyright (C) 2000 by David A. Capello

all:
	gcc -c suma.c -o suma.o
	ar rs libsuma.a suma.o
	gcc -c main.c -o main.o
	gcc -L. -o suma.exe main.o -lsuma
