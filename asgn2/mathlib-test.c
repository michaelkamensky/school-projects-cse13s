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

void do_euler(int stat) {
    double pi_math = M_PI;
    double pi_result = pi_euler();
    printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_result, pi_math, pi_result - pi_math);
    if(stat) {
        printf("pi_euler() terms = %d\n", pi_euler_terms());
    }

}

void do_madhava(int stat) {
    double pi_math = M_PI;
    double pi_result = pi_madhava();
    printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_result, pi_math, pi_result - pi_math);
    if(stat) {
        printf("pi_madhava() terms = %d\n", pi_madhava_terms());
    }

}

void do_newton(int stat) {
    double sqr2_math = M_SQRT2;
    double sqr2_result = sqrt_newton(2);
    printf("sqrt_newton() = %16.15lf, M_SQRT2 = %16.15lf, diff = %16.15lf\n", sqr2_result, sqr2_math, sqr2_result - sqr2_math);
    if(stat) {
        printf("sqrt_newton() iteration = %d\n", sqrt_newton_iters());
    }

}

void usage(char *exec) {
  fprintf(stderr,
          "SYNOPSIS\n"
          "   Prints approximations for pi and e and compares it to libary values.\n"
          "\n"
          "USAGE\n"
          "   %s [options] \n"
          "\n"
          "OPTIONS\n"
          "    -h display program help and usage.\n"
          "    -e runs Eulers apprximation of e\n"
          "    -b runs Bailey-Borwein-Plouffe apprximation of pi\n"
          "    -v runs Vietes apprximation of pi\n"
          "    -m runs Madhava apprximation of pi\n"
          "    -s sets stats mode shows the number iterations for each approximation\n"
          "    -n Runs Newton-Raphson square root approximation test\n"
          "    -a runs all tests\n",
          exec);
	  
}



int main(int argc, char **argv) {
    int c;
    int need_do_e = 0;
    int need_do_bbp = 0;
    int need_do_viete = 0;
    int need_do_euler = 0;
    int need_do_madhava = 0;
    int need_do_newton = 0;
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
        case 'r':
            need_do_euler = 1;
            break;
        case 'm':
            need_do_madhava = 1;
            break;
	case 'n':
            need_do_newton = 1;
            break;
        case 's':
            use_stats = 1;
            break;
        case 'a':
            need_do_e = 1;
            need_do_bbp = 1;
            need_do_viete = 1;
            need_do_madhava = 1;
            need_do_euler = 1;
            need_do_newton = 1;
            break;
        default: 
            usage(argv[0]);
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

    if (need_do_euler) {
        do_euler(use_stats);
    }

    if (need_do_madhava) {
        do_madhava(use_stats);
    }

    if (need_do_newton) {
        do_newton(use_stats);
    }

    return 0;
}
