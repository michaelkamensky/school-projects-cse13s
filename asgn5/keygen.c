#include <inttypes.h>
#include <time.h>
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
        "   Runs the game of life\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -b : specifies the minimum bits needed for the public modulus n\n"
        "    -i : specifies the number of Miller-Rabin iterations for testing primes (default: 50)\n"
        "    -n pbfile : specifies the public key file (default: ss.pub)\n"
        "    -d pvfile : specifies the private key file (default: ss.priv)\n"
        "    -s : specifies the random seed for the random state initialization\n"
        "    -v : enables verbose output\n"
        "    -h : display program help and usage\n",
        exec);
}

int main(int argc, char **argv) {
    int c;
    uint32_t min_bits = 256;
    uint32_t iterations = 50;
    char *public_key_file_name = NULL;
    char *private_key_file_name = NULL;
    uint32_t seed = time(NULL);
    bool verbose = false;
    while ((c = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
        switch (c) {
        case 'v': verbose = true; break;
        case 'd':
            private_key_file_name = strdup(optarg); 
            break;
        case 'n':
            public_key_file_name = strdup(optarg); 
            break;
        case 'i': iterations = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'b': min_bits = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 's': seed = (uint32_t) strtoul(optarg, NULL, 10); break;
        default: usage(argv[0]); exit(-1);
        }
    }

    randstate_init(seed);

    // Initializing mpz_t vars
    mpz_t n, p, q, pq, d;
    mpz_inits(n, p, q, pq, d, NULL);
    ss_make_pub(p, q, n, min_bits, iterations);
    ss_make_priv(d, pq, p, q);
    char *username = getenv("USER");

    if (!public_key_file_name) {
        public_key_file_name = strdup("ss.pub");
    }
    FILE *public_key_file;
    public_key_file = fopen(public_key_file_name, "w");
    ss_write_pub(n, username, public_key_file);
    fclose(public_key_file);

    if (!private_key_file_name) {
        private_key_file_name = strdup("ss.priv");
    }
    FILE *private_key_file;
    private_key_file = fopen(private_key_file_name, "w");
    ss_write_priv(pq, d, private_key_file);
    fclose(private_key_file);

    // if verbose = true then print out the values
    if (verbose) {
        printf("user = %s\n", username);
        size_t p_bits = mpz_sizeinbase(p, 2);
        gmp_printf("p  (%zu bits) = %Zd\n", p_bits, p);
        size_t q_bits = mpz_sizeinbase(q, 2);
        gmp_printf("q  (%zu bits) = %Zd\n", q_bits, q);
        size_t n_bits = mpz_sizeinbase(n, 2);
        gmp_printf("n  (%zu bits) = %Zd\n", n_bits, n);
        size_t pq_bits = mpz_sizeinbase(pq, 2);
        gmp_printf("pq (%zu bits) = %Zd\n", pq_bits, pq);
        size_t d_bits = mpz_sizeinbase(d, 2);
        gmp_printf("d  (%zu bits) = %Zd\n", d_bits, d);
    }

    mpz_clears(n, p, q, pq, d, NULL);
    randstate_clear();
    free(public_key_file_name);
    free(private_key_file_name);
    return 0;
}
