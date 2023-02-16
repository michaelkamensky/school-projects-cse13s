#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"

void test_pow_mod(uint32_t av, uint32_t dv, uint32_t nv) {
    mpz_t o, a, d, n;
    mpz_inits(o, a, d, n, NULL);
    mpz_set_ui(a, av);
    mpz_set_ui(d, dv);
    mpz_set_ui(n, nv);
    mpz_powm(o, a, d, n);
    gmp_printf("mpz_powm(%Zd, %Zd, %Zd, %Zd)\n", o, a, d, n);
    pow_mod(o, a, d, n);
    gmp_printf("pom_mod(%Zd, %Zd, %Zd, %Zd)\n", o, a, d, n);
}

void test_gcd(uint32_t av, uint32_t bv) {
    mpz_t o, a, b;
    mpz_inits(o, a, b, NULL);
    mpz_set_ui(a, av);
    mpz_set_ui(b, bv);
    gcd(o, a, b);
    gmp_printf("gcd(%Zd, %Zd, %Zd)\n", o, a, b);

}

void test_mod_inverse(uint32_t av, uint32_t bv) {
    mpz_t o, a, b;
    mpz_inits(o, a, b, NULL);
    mpz_set_ui(a, av);
    mpz_set_ui(b, bv);
    mod_inverse(o, a, b);
    gmp_printf("mod_inverse(%Zd, %Zd, %Zd)\n", o, a, b);

}


int main(int argc, char **argv) {
#if 0
    test_pow_mod(100, 500, 333);
    test_pow_mod(30, 5, 3);
    test_pow_mod(323, 655, 3);
    test_pow_mod(33, 157, 6);
    test_pow_mod(2000000, 50000, 3333);
    test_pow_mod(67843, 12345, 789);
#endif
#if 0
    test_gcd(9, 3);
    test_gcd(9, 6);
    test_gcd(9, 18);
    test_gcd(137 * 5* 6, 137 * 7);
#endif
# if 1
    test_mod_inverse(3, 26);
    test_mod_inverse(3, 11);
    test_mod_inverse(17, 23);
    test_mod_inverse(4, 9);
    test_mod_inverse(7, 26);
    test_mod_inverse(13, 2436);
    test_mod_inverse(13, 2435);
    test_mod_inverse(13, 4);
#endif
    return 0;
}

