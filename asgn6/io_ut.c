#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "io.h"
#include "code.h"

int main(void) {
    char *in_file_name = "burger_test.txt";
    int in_file_int = open(in_file_name, O_RDONLY);
    int read_this_bytes = 1000;
    uint8_t *buf = (uint8_t *) calloc(read_this_bytes, sizeof(uint8_t));
    int bytes_r = read_bytes(in_file_int, buf, read_this_bytes);
    close(in_file_int);

    // testing the write capabilities
    char *out_file_name = "test_write.txt";
    int out_file_int = open(out_file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    int write_this_bytes = 50;
    FileHeader h;
    memset(&h, 0, sizeof(FileHeader));
    h.magic = MAGIC;
    h.protection = 10;
    write_header(out_file_int, &h);
    int bytes_w = write_bytes(out_file_int, buf, write_this_bytes);
    close(out_file_int);

    in_file_int = open(out_file_name, O_RDONLY);
    // testing  read_header(int infile, FileHeader *header) 
    FileHeader h2;
    read_header(in_file_int, &h2);
    return 0;
}
