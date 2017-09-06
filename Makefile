CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -g -Werror -Wextra -Wmissing-declarations

all:mpasswdsort

mpasswdsort:list.o mpasswdsort.c
	$(CC) mpasswdsort.c list.o $(CFLAGS) -o mpasswdsort

list.o:list.h list.c
	$(CC) -c $(CFLAGS) list.c


clean:
	rm -f list mpasswdsort *.o core
