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

}

void test_ss_read_pub(FILE *f) {
    mpz_t n;
    mpz_inits(n, NULL);
    char username[] = "";
    ss_read_pub(n, username, f);
    gmp_printf("%Zd\n", n);
    printf("%s\n", username);

}

int main(int argc, char **argv) {
    FILE *f_out = fopen("test_out.txt", "w");
    test_ss_write_pub(42, "mkamensk", f_out); 
    fclose(f_out);
    FILE *f_in = fopen("test_in.txt", "r");
    test_ss_read_pub(f_in);
    fclose(f_in);

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

