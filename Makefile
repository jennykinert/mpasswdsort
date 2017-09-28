CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -g -Werror -Wextra -Wmissing-declarations

all:mpasswdsort
  
mpasswdsort:list.o mpasswdsort.o
	$(CC) mpasswdsort.o list.o -o mpasswdsort

list.o:list.h list.c
	$(CC) -c $(CFLAGS) list.c

mpasswdsort.o: mpasswdsort.c mpasswdsort.h
	$(CC) -c $(CFLAGS) mpasswdsort.c
  
clean:
	rm -f list mpasswdsort *.o core

