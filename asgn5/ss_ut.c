#include <stdio.h>
#include <gmp.h>
#include "ss.h"
#include "numtheory.h"
#include "randstate.h"

void test_ss_write_pub(uint32_t av, char username[], FILE *f) {
    mpz_t n;
    mpz_inits(n, NULL);
    mpz_set_ui(n, av);
    ss_write_pub(n, username, f);
    mpz_clears(n, NULL);


}

void test_ss_read_pub(FILE *f) {
    mpz_t n;
    mpz_inits(n, NULL);
    char username[] = "";
    ss_read_pub(n, username, f);
    gmp_printf("%Zd\n", n);
    printf("%s\n", username);
    mpz_clears(n, NULL);

}

void test_ss_make_pub(uint64_t nbits, uint64_t iters) {
    mpz_t n, p, q;
    mpz_inits(n, p, q, NULL);
    ss_make_pub(p, q, n, nbits, iters);
    gmp_printf("n = %Zd, p = %Zd, q = %Zd\n", n, p, q);
    mpz_clears(n, p, q, NULL);

}


int main(int argc, char **argv) {
    FILE *f_out = fopen("test_out.txt", "w");
    test_ss_write_pub(42, "mkamensk", f_out); 
    fclose(f_out);
    FILE *f_in = fopen("test_in.txt", "r");
    test_ss_read_pub(f_in);
    fclose(f_in);
    randstate_init(1);
    test_ss_make_pub(30, 10);
    test_ss_make_pub(256, 20);
    test_ss_make_pub(1024, 30);
    test_ss_make_pub(2048, 100);
    randstate_clear();

#if 0
    test_pow_mod(111, 17, 137);
    test_pow_mod(41, 2, 137);
    test_pow_mod(100, 500, 333);
    test_pow_mod(30, 5, 3);
    test_pow_mod(323, 655, 3);
    test_pow_mod(33, 157, 6);
    test_pow_mod(2000000, 50000, 3333);
    test_pow_mod(67843, 12345, 789);
#endif
    return 0;
}

