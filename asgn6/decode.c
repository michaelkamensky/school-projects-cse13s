#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "io.h"
#include "code.h"
#include "word.h"

int bit_length(uint16_t val) {
    int i;
    for (i = 16; i >= 0; i--) {
        if (val & (1 << i)) {
            return i + 1;
        }
    }
    return 0;
}

void decode(int infile, int outfile) {
    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    int bitlen;
    bool ret;

    while (1) {
        bitlen = bit_length(next_code);
        ret = read_pair(infile, &curr_code, &curr_sym, bitlen);
        // printf("ret = %d, curr_code = %x, curr_sym = %c\n", ret, curr_code, curr_sym);

        if (!ret) {
            break;
        }

        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code += 1;
        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
    }
    flush_words(outfile);
    wt_delete(table);
}

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   decodes the file\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -v : Print compression statistics to stderr\n"
        "    -i <input> : Specify input to compress (stdin by default)\n"
        "    -o <output> : Specify output of compressed input (stdout by default)\n"
        "    -h : display program help and usage.\n",
        exec);
}

int main(int argc, char **argv) {
    int c;
    char *in_file_name = NULL;
    char *out_file_name = NULL;
    bool statistics = false;
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
        switch (c) {
        case 'v': statistics = true; break;
        case 'i': in_file_name = strdup(optarg); break;
        case 'o': out_file_name = strdup(optarg); break;
        default: usage(argv[0]); exit(-1);
        }
    }

    // open right files
    int in_file;
    if (in_file_name) {
        in_file = open(in_file_name, O_RDONLY);
        if (in_file == -1) {
            fprintf(stderr, "Can not open %s file for reading\n", in_file_name);
            usage(argv[0]);
            exit(-1);
        }
    } else {
        in_file = STDIN_FILENO;
    }

    FileHeader header;
    read_header(in_file, &header);

    if (header.magic != MAGIC) {
        printf("Input is not compressed file\n");
        usage(argv[0]);
        exit(-1);
    }

    int out_file;
    if (out_file_name) {
        out_file = open(out_file_name, O_WRONLY | O_CREAT | O_TRUNC, header.protection);
        if (out_file == -1) {
            fprintf(stderr, "Can not open %s file for writing\n", in_file_name);
            usage(argv[0]);
            exit(-1);
        }
    } else {
        out_file = STDOUT_FILENO;
    }

    decode(in_file, out_file);

    // if statistics is true then print of the values
    if (statistics) {
        // write the stats here
        struct stat statbuf_i;
        fstat(in_file, &statbuf_i);
        struct stat statbuf_o;
        fstat(out_file, &statbuf_o);
        fprintf(stderr, "Compressed file size: %lu bytes\n", statbuf_i.st_size);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", statbuf_o.st_size);
        double percent = 100 * (1 - ((double) statbuf_i.st_size / (double) statbuf_o.st_size));
        fprintf(stderr, "Compression ratio: %.2f%% \n", percent);
    }
    // close the right files
    if (out_file_name) {
        close(out_file);
    }
    if (in_file_name) {
        close(in_file);
    }

    free(in_file_name);
    free(out_file_name);
    return 0;
}
