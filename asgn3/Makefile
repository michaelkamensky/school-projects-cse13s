SHELL := /bin/sh
CC = clang
#CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -O2 $(MYCFLAGS) 
#CFLAGS = -g $(MYCFLAGS)
#CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
objects = batcher.o  shell.o  heap.o  quick.o  set.o  stats.o sorting.o


all: sorting set_ut

sorting: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects)

set_ut: set_ut.o set.o
	$(CC) $(CFLAGS) -o $@ set_ut.o set.o

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c $<

shell.o: shell.c gaps.h
	$(CC) $(CFLAGS) -c $<

heap.o: heap.c
	$(CC) $(CFLAGS) -c $<

quick.o: quick.c
	$(CC) $(CFLAGS) -c $<

set.o: set.c
	$(CC) $(CFLAGS) -c $<

stats.o: stats.c
	$(CC) $(CFLAGS) -c $<

set_ut.o: set_ut.c
	$(CC) $(CFLAGS) -c $< 

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c $<

gaps.h: gaps.h.py
	./gaps.h.py > $@

clean:
	rm -f sorting $(objects) gaps.h set_ut set_ut.o

format:
	clang-format -i -style=file *.[ch]

