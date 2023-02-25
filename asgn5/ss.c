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
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
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
    mpz_inits(q_1, p_1, pp, mod1, mod2, NULL);
    uint64_t upper = ((2 * nbits) / 5);
    uint64_t lower = (nbits / 5);
    // generates a random value from lower to upper
    uint64_t p_bits = (rand() % (upper - lower + 1)) + lower;
    uint64_t q_bits = nbits - (2 * p_bits);
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
    mpz_clears(q_1, p_1, pp, mod1, mod2, NULL);
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
void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t q_1, p_1, lcm, n, p_1_x_q_1, g_c_d;
    mpz_inits(q_1, p_1, lcm, n, p_1_x_q_1, g_c_d, NULL);
    // p_1 = p - 1
    mpz_sub_ui(p_1, p, 1);
    // q_1 = q - 1
    mpz_sub_ui(q_1, q, 1);
    // lcm = lcm(p_1, q_1)
    gcd(g_c_d, p_1, q_1);
    mpz_mul(p_1_x_q_1, p_1, q_1);
    mpz_fdiv_q(lcm, p_1_x_q_1, g_c_d);
    // pq = p * q
    mpz_mul(pq, p, q);
    // n = n * pq
    mpz_mul(n, pq, p);
    // d = mod_inverse(pq, lcm)
    mod_inverse(d, n, lcm);
    mpz_clears(q_1, p_1, lcm, n, NULL);
}

//
// Export SS private key to output stream
//
// Requires:
//  pq: private modulus
//  d:  private exponent
//  pvfile: open and writable file stream
//
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", pq);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

//
// Import SS private key from input stream
//
// Provides:
//  pq: private modulus
//  d:  private exponent
//
// Requires:
//  pvfile: open and readable file stream
//  all mpz_t arguments to be initialized
//
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", pq);
    gmp_fscanf(pvfile, "%Zx\n", d);
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
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
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
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    // m = pow_mod(c, d, pq)
    pow_mod(m, c, d, pq);
}

//
// Encrypt an arbitrary file
//
// Provides:
//  fills outfile with the encrypted contents of infile
//
// Requires:
//  infile: open and readable file stream
//  outfile: open and writable file stream
//  n: public exponent and modulus
//
void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    mpz_t m, c, ntemp;
    mpz_inits(m, c, ntemp, NULL);
    // ntemp = n
    mpz_set(ntemp, n);
    // ntemp = sqrt(ntemp);
    mpz_sqrt(ntemp, ntemp);
    // ntemp = log(ntemp, 2)
    size_t k = mpz_sizeinbase(ntemp, 2);
    k = k - 1;
    k = k / 8;
    // I don't understand why but to match example need to sub one from k
    k = k - 1;
    uint8_t *buffer = (uint8_t *) calloc(k, sizeof(uint8_t));
    buffer[0] = 0xFF;
    uint32_t j;
    while (1) {
        j = fread(&buffer[1], sizeof(uint8_t), k - 1, infile);
        if (j == 0) {
            break;
        }
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, buffer);
        ss_encrypt(c, m, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    }
    free(buffer);
    mpz_clears(m, c, ntemp, NULL);
}

//
// Decrypt a file back into its original form.
//
// Provides:
//  fills outfile with the unencrypted data from infile
//
// Requires:
//  infile: open and readable file stream to encrypted data
//  outfile: open and writable file stream
//  d: private exponent
//  pq: private modulus
//
void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    size_t k = mpz_sizeinbase(pq, 2);
    k = k - 1;
    k = k / 8;
    uint8_t *buffer = (uint8_t *) calloc(k, sizeof(uint8_t));
    size_t j;
    while (EOF != gmp_fscanf(infile, "%Zx\n", c)) {
        ss_decrypt(m, c, d, pq);
        mpz_export(buffer, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(&buffer[1], sizeof(uint8_t), j - 1, outfile);
    }
    free(buffer);
    mpz_clears(c, m, NULL);
}
