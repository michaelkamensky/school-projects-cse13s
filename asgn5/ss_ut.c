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

void test_ss_priv(uint64_t nbits, uint64_t iters, char *write_file_name) {
    // publci key gen
    mpz_t n, p, q;
    mpz_inits(n, p, q, NULL);
    ss_make_pub(p, q, n, nbits, iters);
    //gmp_printf("n = %Zd, p = %Zd, q = %Zd\n", n, p, q);

    // private key gen
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);
    //ss_make_priv(d, pq, p, q);
    //gmp_printf("p = %Zd, q = %Zd\n", p, q);
    //gmp_printf("d = %Zd, pq = %Zd\n", d, pq);

    // open file to write
    //FILE *out_file = fopen(write_file_name, "w");
    FILE *out_file = fopen(write_file_name, "r");

    // try write
    //ss_write_priv(pq, d, out_file);
    ss_read_priv(pq, d, out_file);
    gmp_printf("d = %Zx, pq = %Zx\n", d, pq);

    //close files
    //fclose(in_file);
    fclose(out_file);
}

void test_ss(uint64_t nbits, uint64_t iters, uint32_t mv) {
    // publci key gen
    mpz_t n, p, q;
    mpz_inits(n, p, q, NULL);
    ss_make_pub(p, q, n, nbits, iters);
    gmp_printf("n = %Zd, p = %Zd, q = %Zd\n", n, p, q);

    // private key gen
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);
    ss_make_priv(d, pq, p, q);
    gmp_printf("p = %Zd, q = %Zd\n", p, q);
    gmp_printf("d = %Zd, pq = %Zd\n", d, pq);

    // encryption
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    mpz_set_ui(m, mv);
    ss_encrypt(c, m, n);
    gmp_printf("ss_encrypt(%Zd, %Zd, %Zd)\n", c, m, n);

    // decryption
    mpz_t out;
    mpz_inits(out, NULL);
    ss_decrypt(out, c, d, pq);
    gmp_printf("ss_decrypt(%Zd, %Zd, %Zd, %Zd)\n", out, c, d, pq);

    mpz_clears(d, pq, NULL);
    mpz_clears(n, p, q, NULL);
    mpz_clears(c, m, NULL);
    mpz_clears(out, NULL);
}

void test_ss_file(uint64_t nbits, uint64_t iters, char *clear_file_name, char *enc_file_name,
    char *clear2_file_name) {
    // publci key gen
    mpz_t n, p, q;
    mpz_inits(n, p, q, NULL);
    ss_make_pub(p, q, n, nbits, iters);
    gmp_printf("n = %Zd, p = %Zd, q = %Zd\n", n, p, q);

    // private key gen
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);
    ss_make_priv(d, pq, p, q);
    gmp_printf("p = %Zd, q = %Zd\n", p, q);
    gmp_printf("d = %Zd, pq = %Zd\n", d, pq);

    // open files
    FILE *in_file = fopen(clear_file_name, "r");
    FILE *out_file = fopen(enc_file_name, "w");

    // run encrypt file
    ss_encrypt_file(in_file, out_file, n);

    //close files
    fclose(in_file);
    fclose(out_file);

    // new files
    in_file = fopen(enc_file_name, "r");
    out_file = fopen(clear2_file_name, "w");

    //run decrypt file
    ss_decrypt_file(in_file, out_file, d, pq);
}

int main(void) {
#if 0
    FILE *f_out = fopen("test_out.txt", "w");
    test_ss_write_pub(42, "mkamensk", f_out); 
    fclose(f_out);
    FILE *f_in = fopen("test_in.txt", "r");
    test_ss_read_pub(f_in);
    fclose(f_in);
#endif
    randstate_init(1);
    test_ss_file(1024, 50, "DESIGN2.pdf", "DESIGN_ENC.pdf", "DESIGN3.pdf");
    //test_ss_priv(1024, 50, "write_priv.txt", "read_priv.txt");
#if 0
    test_ss(256, 50, 1000000);
    test_ss(256, 50, 0); // not suppoused to encrypt
    test_ss(1024, 50, 1); // not suppoused to encrypt
    test_ss(1024, 50, 2);
    test_ss(2048, 100, 999999999);
#endif
#if 0
    test_ss_make_pub(30, 10);
    test_ss_make_pub(256, 20);
    test_ss_make_pub(1024, 30);
    test_ss_make_pub(2048, 100);
#endif
    randstate_clear();

    return 0;
}
