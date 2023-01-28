#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mathlib.h"

int
main (int argc, char **argv){
    int c;    
    double e_result  = e();
    printf("The result of the e functio is %f\n",e_result);
    double e_iterations = e_terms();
    printf("The number of iterations is %f\n",e_iterations);
    double madhava_res = pi_madhava();
    printf("The madhava pi estimat is %f\n",madhava_res);
    double euler_pi = pi_euler();
    printf("The euler pi estimate is %f\n", euler_pi);
    printf("The bbp estimate is %f\n", pi_bbp());
    while ((c = getopt (argc, argv, "e")) != -1) {
        switch (c) {
           case 'e':
           e();
           break;
        default:
           printf("option not understood");
           exit(-1);
        }
    }
   return 0;
 
}

