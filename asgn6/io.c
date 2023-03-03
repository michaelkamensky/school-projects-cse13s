#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "word.h"
#include "code.h"

uint64_t total_syms;
uint64_t total_bits;

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int result = 0;
    ssize_t bytes_read = read(infile, buf, to_read);
    result = (int) bytes_read;
    while (result > ) {
        bytes_read = read(infile, buf, to_read);
         result += (int) bytes_read;
    }
    return result;
}
