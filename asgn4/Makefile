SHELL := /bin/sh
CC = clang
#CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -O2 $(MYCFLAGS) 
#CFLAGS = -g $(MYCFLAGS)
#CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
objects = life.o universe.o 


all: life

life: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects)

life.o: life.c
	$(CC) $(CFLAGS) -c $<

universe.o: universe.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f life $(objects)

format:
	clang-format -i -style=file *.[ch]

