#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "code.h"

int main(void) {
    char *in_file_name = "burger_test.txt";
    FILE *in_file = fopen(in_file_name, "w");
    int in_file_int = fileno(in_file);
    int read_this_bytes = 50;
    uint8_t *buf = (uint8_t *) calloc(read_this_bytes, sizeof(uint8_t));
    int bytes = read_bytes(in_file_int, buf, read_this_bytes);
}
