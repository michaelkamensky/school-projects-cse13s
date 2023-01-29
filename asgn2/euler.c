#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_euler(void) {
    double pi = 0.0;
    double last = 1.0;
    double k = 1.0;
    count = 0;

    while ((last) > EPSILON) {
        last = 1.0 / (k * k);
        pi += last;
        k += 1;
        count += 1;
#ifdef TRACE_PI
        if (count % 100000 == 0) {
            double tot = sqrt_newton(6 * pi);
            printf("%d %16.15lf\n", count, tot);
        }
#endif
    }
    return sqrt_newton(6 * pi);
}

int pi_euler_terms(void) {
    return count;
}
