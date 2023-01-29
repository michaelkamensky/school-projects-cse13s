#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_viete(void) {
    double two_over_pi = 1.0;
    double last = 1.0;
    double numerator = 0.0;
    double pi = 0.0;
    double previous_pi = 1.0;
    count = 0;

    while (absolute(pi - previous_pi) > EPSILON) {
        previous_pi = pi;
        numerator = sqrt_newton((2.0 + numerator));
        last = numerator / 2.0;
        two_over_pi *= last;
        pi = 2.0 / two_over_pi;
        count += 1;
#ifdef TRACE_PI
        printf("%d %16.15lf\n", count, pi);
#endif
    }
    return pi;
}

int pi_viete_factors(void) {
    return count;
}
