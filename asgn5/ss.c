#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdio.h>

#include "ss.h"
#include "numtheory.h"

//
// Export SS public key to output stream
//
// Requires:
//  n: public modulus/exponent
//  username: login name of keyholder ($USER)
//  pbfile: open and writable file stream
//
void ss_write_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
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
    gmp_fscanf(pbfile, "%Zx\n", n); 
    fscanf(pbfile, "%s\n", username);
}

//
// Generates the components for a new SS key.
//
// Provides:
//  p:  first prime
//  q: second prime
//  n: public modulus/exponent
//
// Requires:
//  nbits: minimum # of bits in n
//  iters: iterations of Miller-Rabin to use for primality check
//  all mpz_t arguments to be initialized
//
void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    mpz_t q_1, p_1, pp, mod1, mod2;    
    mpz_inits( q_1, p_1, pp, mod1, mod2, NULL);
    uint64_t upper = ((2*nbits)/5);
    uint64_t lower = (nbits/5);
    // generates a random value from lower to upper
    uint64_t p_bits = (rand() % (upper - lower + 1)) + lower;
    uint64_t q_bits = nbits - (2*p_bits);
    while (true) {
        // make p prime
        make_prime(p, p_bits, iters);
        // make q prime
        make_prime(q, q_bits, iters);
        // p_1 = p - 1
        mpz_sub_ui(p_1, p, 1);
        // q_1 = q - 1
        mpz_sub_ui(q_1, q, 1);
        // mod1 = p % q_1
        mpz_mod(mod1, p, q_1);
        // mod2 = q % p_1
        mpz_mod(mod2, q, p_1);
        // if ((mod1 != 0) and (mod2 != 0))
        if ((mpz_cmp_ui(mod1, 0) != 0) && (mpz_cmp_ui(mod2, 0) != 0)) {
            break;
        }
    }
    // pp = p^2
    mpz_pow_ui(pp, p, 2);
    // n = pp * q
    mpz_mul(n, pp, q);
    mpz_clears( q_1, p_1, pp, mod1, mod2, NULL);
}

//
// Generates components for a new SS private key.
//
// Provides:
//  d:  private exponent
//  pq: private modulus
//
// Requires:
//  p:  first prime number
//  q: second prime number
//  all mpz_t arguments to be initialized
//
void ss_make_priv(mpz_t d, mpz_t pq, mpz_t p, mpz_t q) {
    mpz_t q_1, p_1, lcm, n;
    mpz_inits( q_1, p_1, lcm, n, NULL);
    // p_1 = p - 1
    mpz_sub_ui(p_1, p, 1);
    // q_1 = q - 1
    mpz_sub_ui(q_1, q, 1);
    // lcm = lcm(p_1, q_1)
    mpz_lcm(lcm, p_1, q_1);
    // pq = p * q
    mpz_mul(pq, p, q);
    // n = n * pq
    mpz_mul(n, pq, p);
    // d = mod_inverse(pq, lcm)
    mod_inverse(d, n, lcm);
}

//
// Encrypt number m into number c
//
// Provides:
//  c: encrypted integer
//
// Requires:
//  m: original integer
//  n: public exponent/modulus
//  all mpz_t arguments to be initialized
//
void ss_encrypt(mpz_t c, mpz_t m, mpz_t n) {
    // c = pow_mod(m, n, n)
    pow_mod(c, m, n, n);
}

//
// Decrypt number c into number m
//
// Provides:
//  m: decrypted/original integer
//
// Requires:
//  c: encrypted integer
//  d: private exponent
//  pq: private modulus
//  all mpz_t arguments to be initialized
//
void ss_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t pq){
    // m = pow_mod(c, d, pq)
    pow_mod(m, c, d, pq);
}
