SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
objects = bbp.o  e.o  euler.o  madhava.o  mathlib-test.o  newton.o

all: mathlib-test

mathlib-test: $(objects)
	$(CC) $(CFLAGS) -o mathlib-test $(objects)

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f mathlib-test $(objects) 

format:
	clang-format -i -style=file *.[ch]

