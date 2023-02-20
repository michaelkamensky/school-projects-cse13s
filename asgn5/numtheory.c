#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdio.h>

#include "numtheory.h"
#include "randstate.h"

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
    bool t_return = true;
    mpz_t r, pr, t, pt, q, temp1, temp2, temp3;
    mpz_inits(r, pr, t, pt, q, temp1, temp2, temp3, NULL);
    mpz_set(r, n);
    mpz_set(pr, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(pt, 1);
    while (mpz_cmp_ui(pr, 0) != 0) {
        mpz_fdiv_q(q, r, pr);

        mpz_set(temp1, pr);
        mpz_mul(temp2, q, pr);
        mpz_sub(temp3, r, temp2);
        mpz_set(r, temp1);
        mpz_set(pr, temp3);

        mpz_set(temp1, pt);
        mpz_mul(temp2, q, pt);
        mpz_sub(temp3, t, temp2);
        mpz_set(t, temp1);
        mpz_set(pt, temp3);
    }

    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(o, 0);
        t_return = false;
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
        mpz_set(o, t);
        t_return = false;
    }
    if (t_return) {
        mpz_set(o, t);
    }
    mpz_clears(r, pr, t, pt, q, temp1, temp2, temp3, NULL);
}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t p, v, vxp, pxp, dtemp;
    mpz_inits(p, v, vxp, pxp, dtemp, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, a);
    mpz_set(dtemp, d);
    while (mpz_cmp_ui(dtemp, 0) > 0) {
        if (mpz_odd_p(dtemp)) {
            mpz_mul(vxp, v, p);
            mpz_mod(v, vxp, n);
        }
        mpz_mul(pxp, p, p);
        mpz_mod(p, pxp, n);
        mpz_fdiv_q_ui(dtemp, dtemp, 2);
    }
    mpz_set(o, v);
    mpz_clears(p, v, vxp, pxp, dtemp, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
    // special cases
    if ((mpz_cmp_ui(n, 0) == 0) || (mpz_cmp_ui(n, 1) == 0)) {
        return false;
    }
    // more special cases cause we subtract three from n
    if ((mpz_cmp_ui(n, 2) == 0) || (mpz_cmp_ui(n, 3) == 0)) {
        return true;
    }
    mpz_t y, r, j, s, s_1, n_1, n_3, a, two;
    mpz_inits(y, r, j, s, s_1, n_1, n_3, a, two, NULL);

    // r = n - 1
    mpz_sub_ui(r, n, 1);
    // temp2 = n - 1
    mpz_sub_ui(n_1, n, 1);
    // n_3 = n - 3
    mpz_sub_ui(n_3, n, 3);
    // two = 2
    mpz_set_ui(two, 2);

    // write n-1=2^(s)r such that r is odd
    // while (temp1 % 2 == 0)
    while (mpz_even_p(r)) {
        // temp1 = temp1 / 2
        mpz_fdiv_q_ui(r, r, 2);
        // s = s + 1
        mpz_add_ui(s, s, 1);
    }
    for (uint64_t i = 0; i < iters; i++) {
        // choose random a (2,3,...,n-2)
        // gives between 0 and n-4 inclusive
        mpz_urandomm(a, state, n_3);
        // a = a + 2
        // gives between 2 amd n-2 inclusive
        mpz_add_ui(a, a, 2);
        // y = pow_mod(a, r, n)
        pow_mod(y, a, r, n);
        // if ((y != 1) && (y != n_1))
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_1) != 0)) {
            // j = 1
            mpz_set_ui(j, 1);
            // s_1 = s - 1
            mpz_sub_ui(s_1, s, 1);
            // while ((j <= s-1) && (y != n - 1))
            while ((mpz_cmp(j, s_1) <= 0) && mpz_cmp(y, n_1) != 0) {
                // y = pow_mod(2, n)
                pow_mod(y, y, two, n);
                // if (y == 1)
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(y, r, j, s, s_1, n_1, n_3, a, two, NULL);
                    return false;
                }
                // j = j + 1
                mpz_add_ui(j, j, 1);
            }
            // if (y != n -1)
            if (mpz_cmp(y, n_1) != 0) {
                mpz_clears(y, r, j, s, s_1, n_1, n_3, a, two, NULL);
                return false;
            }
        }
    }
    mpz_clears(y, r, j, s, s_1, n_1, n_3, a, two, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t min, min_a_8, bits_a_8, result, two;
    mpz_inits(min, min_a_8, bits_a_8, result, two, NULL);
    // two = 2
    mpz_set_ui(two, 2);
    // min = 2^bits
    mpz_pow_ui(min, two, bits);
    // min_a_8 = 2^(bits_a_8)
    mpz_pow_ui(min_a_8, two, (bits + 8));
    while (true) {
        // result = rand(min, min_a_3)
        mpz_urandomm(result, state, min_a_8);
        // if (result % 2 == 0)
        if (mpz_even_p(result)) {
            // result += 1
            mpz_add_ui(result, result, 1);
        }
        if (mpz_cmp(result, min) < 0) {
            continue;
        }
        // if(result >= min && is_prime(result, iters))
        if (is_prime(result, iters)) {
            // p = result
            break;
        }
    }
    mpz_set(p, result);
    mpz_clears(min, min_a_8, result, two, NULL);
}
