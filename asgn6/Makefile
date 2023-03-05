SHELL := /bin/sh
#CC = clang
CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
CFLAGS += -Wno-error=unused-variable -Wno-error=unused-parameter
#CFLAGS = -g
encode_objects = encode.o trie.o
decode_objects = decode.o trie.o

all: encode decode trie_ut word_ut io_ut

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

trie_ut: trie_ut.o trie.o
	$(CC) $(CFLAGS) -o $@ trie_ut.o trie.o

trie_ut.o: trie_ut.c
	$(CC) $(CFLAGS) -c trie_ut.c

word_ut: word_ut.o word.o
	$(CC) $(CFLAGS) -o $@ word_ut.o word.o

word_ut.o: word_ut.c
	$(CC) $(CFLAGS) -c word_ut.c

word.o: word.c
	$(CC) $(CFLAGS) -c word.c

io_ut: io_ut.o io.o word.o
	$(CC) $(CFLAGS) -o $@ io_ut.o io.o word.o

io_ut.o: io_ut.c
	$(CC) $(CFLAGS) -c io_ut.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f encode decode trie_ut word_ut io_ut *.o

format:
	clang-format -i -style=file *.[ch]

