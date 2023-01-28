#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_e(void) {
    double e_math = M_E;
    double e_result = e();
    printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e_result, e_math, e_result - e_math);
}

void do_bbp(void) {
    double pi_math = M_PI;
    double pi_result = pi_bbp();
    printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_result, pi_math, pi_result - pi_math);
}



int main(int argc, char **argv) {
    int c;
    

#if 0    
    double e_result = e();
    printf("The result of the e functio is %f\n", e_result);
    double e_iterations = e_terms();
    printf("The number of iterations is %f\n", e_iterations);
    double madhava_res = pi_madhava();
    printf("The madhava pi estimat is %f\n", madhava_res);
    double euler_pi = pi_euler();
    printf("The euler pi estimate is %f\n", euler_pi);
    printf("The bbp estimate is %f\n", pi_bbp());
#endif
    while ((c = getopt(argc, argv, "abehmnrsv")) != -1) {
        switch (c) {
        case 'e':
            do_e();
            break;
	case 'b':
            do_bbp();
            break;
        case 'a':
            do_e();
            do_bbp();
            break;
        default: 
            printf("option not understood");
            exit(-1);
        }
	
    }
    return 0;
}
