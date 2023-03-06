#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "io.h"
#include "code.h"
#include "endian.h"

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

void write_header(int outfile, FileHeader *header) {
    FileHeader h = *header;
#if 0
    h->magic = header->magic;
    h->protection = header->protection;
#endif
    if (big_endian()) {
       h.magic = swap32(h.magic);
       h.protection = swap32(h.protection);
 
    }
    write_bytes(outfile, (uint8_t *)&h, sizeof(FileHeader)); 
}

void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
    if (big_endian()) {
        // big endian
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
}
//#undef BLOCK
//#define BLOCK 2

static uint8_t sym_buf[BLOCK];
static size_t sym_current;
static size_t read_sym_buf_size;
bool read_sym(int infile, uint8_t *sym) {
    if (sym_current == 0) {
        read_sym_buf_size = read_bytes(infile, sym_buf, BLOCK);
        if (read_sym_buf_size == 0) {
            // end of file
            return false;
        }
    }

    *sym = sym_buf[sym_current];
    sym_current += 1;
    if (sym_current == read_sym_buf_size){
        sym_current = 0;
        memset( sym_buf, 0, BLOCK);
    }
    return true;
    
}

static uint8_t word_buf[BLOCK];
static size_t word_current;
void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < w->len; i++) {
        word_buf[word_current] = w->syms[i];
        word_current += 1;
        if (word_current == BLOCK) {
            write_bytes(outfile, word_buf, BLOCK);
            word_current = 0;
            memset(word_buf, 0, BLOCK);

        }
    }
}

void flush_words(int outfile){
    write_bytes(outfile, word_buf, word_current);
    word_current = 0;
    memset( word_buf, 0, BLOCK);

}

static uint8_t write_buf[BLOCK];
static size_t write_current_bit;

static void write_bit(int out_fd, uint8_t b) {
    size_t byte_addr = write_current_bit / 8;
    int bit_addr = write_current_bit % 8;
    write_buf[byte_addr] = write_buf[byte_addr] | (b << bit_addr);
    write_current_bit += 1;
    if (write_current_bit == BLOCK * 8) {
        write_bytes(out_fd, write_buf, BLOCK);
        write_current_bit = 0;
        memset( write_buf, 0, BLOCK);
    }
}

static uint8_t read_buf[BLOCK];
static size_t read_buf_size;
static size_t read_current_bit;

static uint8_t read_bit(int in_fd) {
    uint8_t b = 2;

    if (read_current_bit == 0) {
        read_buf_size = read_bytes(in_fd, read_buf, BLOCK);
        if (read_buf_size == 0) {
            // end of file
            return b;
        }
    }

    size_t byte_addr = read_current_bit / 8;
    int bit_addr = read_current_bit % 8;

    if (byte_addr < read_buf_size) {
        b = read_buf[byte_addr] & (1 << bit_addr);
        if (b != 0){
            b = 1;
        }
        read_current_bit += 1;
    }
    if (read_current_bit == read_buf_size * 8) {
        read_current_bit = 0;
        memset(read_buf, 0, BLOCK);
    }
    return b;
}


void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    // printf("code = %4.4x, sym = %2.2x, bitlen = %d\n", code, sym, bitlen);
    for (int i = 0; i < bitlen; i++) {
        uint32_t b = code & (1 << i);
        if (b != 0) {
            b = 1;
        }
        write_bit(outfile, b);
    }
    for (int i = 0; i < 8; i++) {
        uint8_t b = sym & (1 << i);
        if (b != 0) {
            b = 1;
        }
        write_bit(outfile, b);
    }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    uint16_t code_val = 0;
    uint8_t sym_val = 0;
    for (int i = 0; i < bitlen; i++) {
        uint8_t b = read_bit(infile);
        if (b == 2){
            // should not happen
            return false;
        }
        if (b == 1){
            code_val = code_val | (1 << i);
        }
    }
    for (int i = 0; i < 8; i++) {
        uint8_t b = read_bit(infile);
        if (b == 2){
            // should not happen
            return false;
        }
        if (b == 1){
            sym_val = sym_val | (1 << i);
        }
    }
    *code = code_val;
    *sym = sym_val;
    if (code_val == STOP_CODE) {
        return false;
    } else {
        return true;
    }

}

void flush_pairs(int outfile) {
    size_t write_size = write_current_bit / 8;
    if (write_current_bit % 8 != 0) {
        write_size += 1;
    }
    write_bytes(outfile, write_buf, write_size);
    write_current_bit = 0;
    memset( write_buf, 0, BLOCK);
}


void test_write_bit(int out_fd) {
#if 1
    write_pair(out_fd, 0x101, 0xcb, 9);
#else
    write_bit(out_fd, 1);

    write_bit(out_fd, 0);

    write_bit(out_fd, 0);
    write_bit(out_fd, 0);
    write_bit(out_fd, 1);
    write_bit(out_fd, 0);
    write_bit(out_fd, 1);
    write_bit(out_fd, 1);
    write_bit(out_fd, 1);
    write_bit(out_fd, 0);
#endif
#if 1
    write_pair(out_fd, EMPTY_CODE, 0x68, 2);
#else
    write_bit(out_fd, 1);

    write_bit(out_fd, 0);
    
    write_bit(out_fd, 0);
    write_bit(out_fd, 0);
    write_bit(out_fd, 0);
    write_bit(out_fd, 1);
    write_bit(out_fd, 0);
    write_bit(out_fd, 1);
    write_bit(out_fd, 1);
    write_bit(out_fd, 0);
#endif
    write_pair(out_fd, STOP_CODE, 0, 3);
}

void test_read_bit(int in_fd) {
#if 0
    uint8_t b;
    for (int i = 0; i < 1024; i++){

        b = read_bit(in_fd);
        printf("%d\n", b);
        if (b == 2) {
            break;
        }
    }
#endif
    uint16_t code;
    uint8_t sym;
    bool ret;
    ret = read_pair(in_fd, &code, &sym, 2);
    printf("ret = %d, code = %x, sym = %x\n",ret, code, sym);
    if (!ret) {
        return;
    }
    ret = read_pair(in_fd, &code, &sym, 2);
    printf("ret = %d, code = %x, sym = %x\n",ret, code, sym);
    if (!ret) {
        return;
    }
    ret = read_pair(in_fd, &code, &sym, 3);
    printf("ret = %d, code = %x, sym = %x\n",ret, code, sym);
    if (!ret) {
        return;
    }

}

