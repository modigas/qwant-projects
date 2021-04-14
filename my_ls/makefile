# -*- makefile -*-

my_ls: main.o my_ls.o
	gcc main.o my_ls.o -o my_ls

main.o: main.c my_ls.h
	gcc -c main.c

my_ls.o: my_ls.c
	gcc -c my_ls.c