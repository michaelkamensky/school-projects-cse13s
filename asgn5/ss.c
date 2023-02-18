#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdio.h>

#include "ss.h"

//
// Export SS public key to output stream
//
// Requires:
//  n: public modulus/exponent
//  username: login name of keyholder ($USER)
//  pbfile: open and writable file stream
//
void ss_write_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zd\n", n);
    fprintf(pbfile, "%s\n", username);

}

//
// Import SS public key from input stream
//
// Provides:
//  n: public modulus
//  username: $USER of the pubkey creator
//
// Requires:
//  pbfile: open and readable file stream
//  username: requires sufficient space
//  all mpz_t arguments to be initialized
//
void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zd\n", n); 
    fscanf(pbfile, "%s\n", username);
}

