#include "mathlib.h"

#include <stdio.h>

int terms = 0;

double pi_madhava(void) {

    static double total = 0.0;
    static double last = 1.0;
    static double k = 0.0;
    while (absolute((last)) > EPSILON) {
        /*This for loop does the numerator power*/
        int i;
        double res = 1.0;
        for (i = 1; i <= k; ++i) {
            res *= -3.0;
        }
        /*printf("res is %f\n", res);
		printf("total is %f\n", total);*/
        last = 1.0 / ((res) * (2.0 * k + 1.0));
        /*printf("last is %f\n", last);*/
        total += last;
        k += 1.0;
        terms += 1;
#ifdef TRACE_PI
        double pi = (sqrt_newton(12) * total);
        printf("%d %16.15lf\n", terms, pi);
#endif
    }
    return (sqrt_newton(12) * total);
}

int pi_madhava_terms(void) {
    return terms;
}
