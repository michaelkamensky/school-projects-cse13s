#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>

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
        "    -n : specifies the file containing the private key (default: ss.priv)\n"
        "    -v : enables verbose output\n"
        "    -h : display program help and usage.\n",
        exec);
}

int main(int argc, char **argv) {
    int c;
    char *in_file_name = NULL;
    char *out_file_name = NULL;
    char *private_key_file_name = NULL;
    bool verbose = false;
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
        switch (c) {
        case 'v': verbose = true; break;
        case 'n':
            private_key_file_name = strdup(optarg); 
            break;
        case 'i': in_file_name = strdup(optarg); break;
        case 'o': out_file_name = strdup(optarg); break;
        default: usage(argv[0]); exit(-1);
        }
    }

    // intializing the vars 
    mpz_t pq, d;
    mpz_inits(pq, d, NULL);

    // open the private keyfile
    if (!private_key_file_name) {
    private_key_file_name = strdup("ss.priv");
    }
    FILE *private_key_file;
    private_key_file = fopen(private_key_file_name, "r");
    ss_read_priv(pq, d, private_key_file);
    fclose(private_key_file);

    // if verbose is true the print out the values
    if (verbose) {
        size_t pq_bits = mpz_sizeinbase(pq, 2);
        gmp_printf("pq (%zu bits) = %Zd\n", pq_bits, pq);
        size_t d_bits = mpz_sizeinbase(d, 2);
        gmp_printf("d  (%zu bits) = %Zd\n", d_bits, d);
    }


    // open the files
    FILE *in_file;
    if (in_file_name) {
        in_file = fopen(in_file_name, "r");
    } else {
        in_file = stdin;
    }

    FILE *out_file;
    if (out_file_name) {
        out_file = fopen(out_file_name, "w");
    } else {
        out_file = stdout;
    }

    // decrypt the files
    ss_decrypt_file(in_file, out_file, d, pq); 

    // close the files
    if (out_file_name) {
        fclose(out_file);
    }
    if (in_file_name) {
        fclose(in_file);
    }

    mpz_clears(pq, d, NULL);
    free(in_file_name);
    free(private_key_file_name);
    free(out_file_name);
    return 0;
}
