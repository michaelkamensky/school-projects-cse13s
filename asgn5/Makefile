SHELL := /bin/sh
CC = clang
#CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g $(shell pkg-config --cflags gmp)
#CFLAGS = -g
LFLAGS = $(shell pkg-config --libs gmp)
decrypt_objects = decrypt.o randstate.o numtheory.o ss.o
encrypt_objects = encrypt.o randstate.o numtheory.o ss.o
keygen_objects = keygen.o randstate.o numtheory.o ss.o


all: decrypt encrypt keygen

decrypt: $(decrypt_objects)
	$(CC) $(CFLAGS) -o $@ $(decrypt_objects) $(LFLAGS)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c $<

encrypt: $(encrypt_objects)
	$(CC) $(CFLAGS) -o $@ $(encrypt_objects) $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c $<

keygen: $(keygen_objects)
	$(CC) $(CFLAGS) -o $@ $(keygen_objects) $(LFLAGS)

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

numtheory_ut: numtheory.o numtheory_ut.o randstate.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

ss.o: ss.c
	$(CC) $(CFLAGS) -c $<

ss_ut.o: ss_ut.c
	$(CC) $(CFLAGS) -c $<

ss_ut: ss.o ss_ut.o randstate.o numtheory.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)


clean:
	rm -f decrypt encrypt keygen numtheory_ut randstate_ut ss_ut *.o

format:
	clang-format -i -style=file *.[ch]

