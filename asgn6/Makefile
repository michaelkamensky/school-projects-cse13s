SHELL := /bin/sh
#CC = clang
CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
#CFLAGS = -g
encode_objects = encode.o trie.o
decode_objects = decode.o trie.o

all: encode decode trie_ut

encode: $(encode_objects)
	$(CC) $(CFLAGS) -o $@ $(encode_objects)

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: $(decode_objects)
	$(CC) $(CFLAGS) -o $@ $(decode_objects)

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c

trie_ut: trie_ut.o
	$(CC) $(CFLAGS) -o $@ trie_ut.o trie.o

trie_ut.o: trie_ut.c
	$(CC) $(CFLAGS) -c trie_ut.c


clean:
	rm -f encode decode trie_ut *.o

format:
	clang-format -i -style=file *.[ch]

