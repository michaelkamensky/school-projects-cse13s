#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_bbp(void) {
    double pi = 0.0;
    double last = 1.0;
    double k = 0.0;
    count = 0;

    while ((last) > EPSILON) {
        int i;
        double res = 1.0;
        for (i = 1; i <= k; ++i) {
            res *= 16;
        }
        last = (1.0 / res)
               * ((4 / (8 * k + 1)) - (2 / (8 * k + 4)) - (1 / (8 * k + 5)) - (1 / (8 * k + 6)));
        pi += last;
        k += 1;
        count += 1;
    }
    return pi;
}

int pi_bbp_terms(void) {
    return count;
}
