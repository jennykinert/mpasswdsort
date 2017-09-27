CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -g -Werror -Wextra -Wmissing-declarations

all:mpasswdsort

mpasswdsort:mpasswdsort.o 
	$(CC) -c $(CFLAGS) mpasswdsort.o list.o -o mpasswdsort

mpasswdsort.o:mpasswdsort.c 
	$(CC) -c $(CFLAGS) mpasswdsort.c

list.o:list.c list.h
	$(CC) -c $(CFLAGS) list.c

clean: 
	rm *o mpasswdsort

