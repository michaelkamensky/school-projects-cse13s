SHELL := /bin/sh
CC = clang
#CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
#CFLAGS = -g

all: encode decode

encode: encode.o
	$(CC) $(CFLAGS) -o $@ encode.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o
	$(CC) $(CFLAGS) -o $@ decode.o

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c


clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.[ch]

