#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "word.h"
#include "code.h"

uint64_t total_syms;
uint64_t total_bits;

int read_bytes(int infile, uint8_t *buf, int to_read) {
    // check if the infile if valid
    if (infile == -1) {
        printf("There was an error in read_bytes faulty file int was passed");
        return 0;
    }
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

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    // check if the outfile if valid
    if (outfile == -1) {
        printf("There was an error in write_bytes faulty file int was passed");
        return 0;
    }
    ssize_t bytes_writen;
    int total_wrote = 0;
    while (1) {
        bytes_writen = write(outfile, buf + total_wrote, to_write - total_wrote);
        total_wrote += bytes_writen;
        if (bytes_writen == 0) {
            break;
        }
        if (total_wrote == to_write) {
            break;
        }
    }
    return total_wrote;
}
