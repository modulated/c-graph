CC=clang
CFLAGS=-std=c11 -Wall -pedantic -Werror -g 

main: graph.c graph.h main.c
	$(CC) $(CFLAGS) main.c graph.c -o main

test: test.c graph.h graph.c
	$(CC) $(CFLAGS) test.c graph.c -o test
