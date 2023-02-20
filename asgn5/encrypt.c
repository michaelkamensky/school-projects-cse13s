#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>
#include <limits.h>

#include "ss.h"
#include "randstate.h"
#include "numtheory.h"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Decrypts file\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -i input : specifices the input file to decrypt (default: stdin)\n"
        "    -o output : specifies the output file to decrypt (default: stdout)\n"
        "    -n : specifies the file containing the public key (default: ss.pub)\n"
        "    -v : enables verbose output\n"
        "    -h : display program help and usage.\n",
        exec);
}

int main(int argc, char **argv) {
    int c;
    char *in_file_name = NULL;
    char *out_file_name = NULL;
    char *public_key_file_name = NULL;
    bool verbose = false;
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
        switch (c) {
        case 'v': verbose = true; break;
        case 'n': public_key_file_name = strdup(optarg); break;
        case 'i': in_file_name = strdup(optarg); break;
        case 'o': out_file_name = strdup(optarg); break;
        default: usage(argv[0]); exit(-1);
        }
    }
    // create the mpz_t and vars that are needed
    mpz_t n;
    mpz_inits(n, NULL);
    char username[LOGIN_NAME_MAX];

    // open the pubkey file to get the value of n
    if (!public_key_file_name) {
        public_key_file_name = strdup("ss.pub");
    }
    FILE *public_key_file;
    public_key_file = fopen(public_key_file_name, "r");
    if (public_key_file == NULL) {
        fprintf(stderr, "Can not open %s file\n", public_key_file_name);
        usage(argv[0]);
        exit(-1);
    }
    // reading pub_key_value
    ss_read_pub(n, username, public_key_file);
    fclose(public_key_file);

    // if verbose is true then print of the values
    if (verbose) {
        printf("user = %s\n", username);
        size_t n_bits = mpz_sizeinbase(n, 2);
        gmp_printf("n (%zu bits) = %Zd\n", n_bits, n);
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

    // encrpyt files
    ss_encrypt_file(in_file, out_file, n);

    if (out_file_name) {
        fclose(out_file);
    }
    if (in_file_name) {
        fclose(in_file);
    }

    mpz_clears(n, NULL);
    free(in_file_name);
    free(public_key_file_name);
    free(out_file_name);
    return 0;
}
