SHELL := /bin/sh
CC = clang
#CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
#CFLAGS = -g
encode_objects = encode.o
decode_objects = decode.o

all: encode decode

encode: $(encode_objects)
	$(CC) $(CFLAGS) -o $@ $(encode_objects)

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: $(decode_objects)
	$(CC) $(CFLAGS) -o $@ $(decode_objects)

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c


clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.[ch]

