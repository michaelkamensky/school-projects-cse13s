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
#include "trie.h"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   encodes the file\n"
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

int bit_length(uint16_t val) {
    int i;
    for (i = 16; i >= 0; i--) {
        if (val & (1 << i)) {
            return i + 1;
        }
    }
    return 0;
}

void encode(int infile, int outfile) {
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t prev_sym = 0;
    uint8_t curr_sym = 0;
    uint16_t next_code = START_CODE;
    bool ret;
    while (1) {
        ret = read_sym(infile, &curr_sym);
        if (!ret) {
            break;
        }
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }
        if (next_code == MAX_CODE) {
            trie_delete(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));
    flush_pairs(outfile);
    trie_delete(root);
    trie_node_delete(root);
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

    // create and write the header to the outfile
    struct stat statbuf;
    FileHeader header;
    memset(&header, 0, sizeof(FileHeader));
    header.magic = MAGIC;
    fstat(in_file, &statbuf);
    header.protection = statbuf.st_mode;

    int out_file;
    if (out_file_name) {
        out_file = open(out_file_name, O_WRONLY | O_CREAT | O_TRUNC, statbuf.st_mode);
        if (out_file == -1) {
            fprintf(stderr, "Can not open %s file for writing\n", out_file_name);
            usage(argv[0]);
            exit(-1);
        }
    } else {
        out_file = STDOUT_FILENO;
    }

    write_header(out_file, &header);

    // encode function
    encode(in_file, out_file);

    // if statistics is true then print of the values
    if (statistics) {
        // write the stats here
        struct stat statbuf_o;
        fstat(out_file, &statbuf_o);
        printf("Compressed file size: %lu bytes\n", statbuf_o.st_size);
        printf("Uncompressed file size: %lu bytes\n", statbuf.st_size);
        double percent = 100 * (1 - ((double) statbuf_o.st_size / (double) statbuf.st_size));
        printf("Compression ratio: %.2f%% \n", percent);
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
