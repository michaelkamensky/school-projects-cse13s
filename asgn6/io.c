#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "word.h"
#include "code.h"

uint64_t total_syms;
uint64_t total_bits;

int read_bytes(int infile, uint8_t *buf, int to_read) {
    ssize_t bytes_read;
    int total_read = 0;
    while (1) {
        bytes_read = read(infile, buf + total_read, to_read - total_read);
        total_read += bytes_read;
        if (bytes_read == 0) {
            break;
        }
        if (total_read == to_read) {
            break;
        }
    }
    return total_read;
}
