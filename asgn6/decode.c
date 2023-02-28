#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

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

    // if statistics is true then print of the values
    if (verbose) {
        // write the stats here
    }

    // open right files
    FILE *in_file;
    if (in_file_name) {
        in_file = fopen(in_file_name, "r");
        if (in_file == NULL) {
            fprintf(stderr, "Can not open %s file\n", in_file_name);
            usage(argv[0]);
            exit(-1);
        }
    } else {
        in_file = stdin;
    }

    FILE *out_file;
    if (out_file_name) {
        out_file = fopen(out_file_name, "w");
    } else {
        out_file = stdout;
    }

    // close the right files
    if (out_file_name) {
        fclose(out_file);
    }
    if (in_file_name) {
        fclose(in_file);
    }

    free(in_file_name);
    free(out_file_name);
    return 0;
}
