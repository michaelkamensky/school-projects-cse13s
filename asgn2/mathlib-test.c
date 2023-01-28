#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_e(int stat) {
    double e_math = M_E;
    double e_result = e();
    printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e_result, e_math, e_result - e_math);
    if(stat) {
        printf("e term = %d\n", e_terms());
    }
}

void do_bbp(int stat) {
    double pi_math = M_PI;
    double pi_result = pi_bbp();
    printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_result, pi_math, pi_result - pi_math);
    if(stat) {
        printf("pi_bbp() term = %d\n", pi_bbp_terms());
    }

}

void do_viete(int stat) {
    double pi_math = M_PI;
    double pi_result = pi_viete();
    printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_result, pi_math, pi_result - pi_math);
    if(stat) {
        printf("pi_viete() factors = %d\n", pi_viete_factors());
    }

}

int main(int argc, char **argv) {
    int c;
    int need_do_e = 0;
    int need_do_bbp = 0;
    int need_do_viete = 0;
    int use_stats = 0;    

    while ((c = getopt(argc, argv, "abehmnrsv")) != -1) {
        switch (c) {
        case 'e':
            need_do_e = 1;
            break;
	case 'b':
            need_do_bbp = 1;
            break;
	case 'v':
            need_do_viete = 1;
            break;
        case 's':
            use_stats = 1;
            break;
        case 'a':
            need_do_e = 1;
            need_do_bbp = 1;
            need_do_viete = 1;
            break;
        default: 
            printf("option not understood");
            exit(-1);
        }
    }

    if (need_do_e) {
        do_e(use_stats);
    }

    if (need_do_bbp) {
        do_bbp(use_stats);
    }

    if (need_do_viete) {
        do_viete(use_stats);
    }






    return 0;
}
