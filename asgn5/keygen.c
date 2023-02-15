#include <inttypes.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    uint32_t min_bits;
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

    if (!private_key_file_name) {
        private_key_file_name = strdup("ss.priv");
    }
    FILE *private_key_file;
    private_key_file = fopen(private_key_file_name, "w");
    fclose(private_key_file);

    if (!public_key_file_name) {
        public_key_file_name = strdup("ss.pub");
    }
    FILE *public_key_file;
    public_key_file = fopen(public_key_file_name, "w");

    free(public_key_file_name);
    free(private_key_file_name);
    return 0;
}
