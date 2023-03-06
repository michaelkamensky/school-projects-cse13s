#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "io.h"
#include "code.h"
#include "word.h"
 
void test_write_bit(int out_fd) {
    write_pair(out_fd, 0x101, 0xcb, 9);
    write_pair(out_fd, EMPTY_CODE, 0x68, 2);
    write_pair(out_fd, STOP_CODE, 0, 3);
}


void test_write_words(int outfile) {
    uint8_t syms[3] = {3, 99, 6};
    Word *w = word_create(syms, 3);
    Word *w1 = word_append_sym(w, 6);
    write_word(outfile, w);
    write_word(outfile, w1);
    write_word(outfile, w);
    write_word(outfile, w1);
    flush_words(outfile);
}

void test_read_bit(int in_fd) {
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

int main(void) {
    char *in_file_name = "burger_test.txt";
    int in_file_int = open(in_file_name, O_RDONLY);

    struct stat statbuf;
    fstat(in_file_int, &statbuf);

    //uint8_t *buf = (uint8_t *) calloc(read_this_bytes, sizeof(uint8_t));
    uint8_t sym;
    //int bytes_r = read_bytes(in_file_int, buf, read_this_bytes);
    while (true) {
        bool res = read_sym(in_file_int, &sym);
        printf("sym = %c, res = %d\n", sym, res);
        if(res) {
            break;
        }
    }
    close(in_file_int);

    // testing the write capabilities
    char *out_file_name = "test_write.txt";
    int out_file_int = open(out_file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    FileHeader h;
    memset(&h, 0, sizeof(FileHeader));
    h.magic = MAGIC;
    h.protection = statbuf.st_mode;
    write_header(out_file_int, &h);
    test_write_bit(out_file_int);
    flush_pairs(out_file_int);
    //int bytes_w = write_bytes(out_file_int, buf, write_this_bytes);
    close(out_file_int);

    in_file_int = open(out_file_name, O_RDONLY);
    // testing  read_header(int infile, FileHeader *header) 
    FileHeader h2;
    read_header(in_file_int, &h2);
    test_read_bit(in_file_int);

    out_file_name = "test_write_words.txt";
    out_file_int = open(out_file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    test_write_words(out_file_int);
    close(out_file_int);
    return 0;
}
