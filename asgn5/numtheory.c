#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdio.h>

#include "numtheory.h"

void gcd(mpz_t g, mpz_t a, mpz_t b) {
    mpz_t t, atemp, btemp;
    mpz_inits(t, atemp, btemp, NULL);
    mpz_set(atemp, a);
    mpz_set(btemp, b);
    while (mpz_cmp_ui(btemp, 0) != 0) {
        mpz_set(t, btemp);
        mpz_mod(btemp, atemp, btemp);
        mpz_set(atemp, t);
    }
    mpz_set(g, atemp);
    mpz_clears(t, btemp, atemp, NULL);
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, pr, t, pt, q, atemp, ntemp, temp1, temp2;
    mpz_inits(r, pr, t, pt, q, atemp, ntemp, temp1, temp2, NULL);    
    mpz_set(atemp, a);
    mpz_set(ntemp, n);
    mpz_set(r, ntemp);
    mpz_set(pr, atemp);
    mpz_set_ui(t, 0);
    mpz_set_ui(pt, 0);
    while (mpz_cmp_ui(pr, 0) != 0) {
        mpz_fdiv_q(q, r, pr);
        mpz_set(temp1, pr);
        mpz_mul(temp2, q, pr);
        mpz_sub(temp2, r, temp2);
        mpz_set(r, temp1);
        mpz_set(pr, temp2);

        mpz_set(temp1, pt);
        mpz_mul(temp2, q, pt);
        mpz_sub(temp2, t, temp2);
        mpz_set(t, temp1);
        mpz_set(pt, temp2);
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(o, 0);
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
        mpz_set(o,t);
    }
    mpz_clears(r, pr, t, pt, q, atemp, ntemp, temp1, temp2, NULL);    
}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t p, temp1, temp2, dtemp;
    mpz_inits(p, temp1, temp2, dtemp, NULL);
    mpz_set_ui(o, 1);
    mpz_set(p, a);
    mpz_set(dtemp, d);
    while (mpz_cmp_ui(dtemp, 0) > 0) {
        if(mpz_odd_p(dtemp)) {
            mpz_mul(temp1, o, p);
            mpz_mod(o, temp1, n);
        }
        mpz_mul(temp2, p, p);
        mpz_mod(p, temp2, n);
        mpz_fdiv_q_ui(dtemp, dtemp, 2);
    }
    mpz_clears(p, temp1, temp2, dtemp, NULL);
}

//bool is_prime(mpz_t n, uint64_t iters);

//void make_prime(mpz_t p, uint64_t bits, uint64_t iters);



