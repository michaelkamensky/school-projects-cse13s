SHELL := /bin/sh
CC = clang
#CC = gcc
#CFLAGS = -Wall -Wpedantic -Werror -Wextra -g 
CFLAGS = -g
LFLAGS = $(shell pkg-config --libs gmp)
decrypt_objects = decrypt.o
encrypt_objects = encrypt.o
keygen_objects = keygen.o


all: decrypt encrypt keygen

decrypt: $(decrypt_objects)
	$(CC) $(CFLAGS) -o $@ $(decrypt_objects)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c $<

encrypt: $(encrypt_objects)
	$(CC) $(CFLAGS) -o $@ $(encrypt_objects)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c $<

keygen: $(keygen_objects)
	$(CC) $(CFLAGS) -o $@ $(keygen_objects)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c $<

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c $<

randstate_ut.o: randstate_ut.c
	$(CC) $(CFLAGS) -c $<

randstate_ut: randstate.o randstate_ut.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c $<

numtheory_ut.o: numtheory_ut.c
	$(CC) $(CFLAGS) -c $<

numtheory_ut: numtheory.o numtheory_ut.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)


clean:
	rm -f decrypt encrypt keygen $(decrypt_objects) $(encrypt_objects) $(keygen_objects)

format:
	clang-format -i -style=file *.[ch]

