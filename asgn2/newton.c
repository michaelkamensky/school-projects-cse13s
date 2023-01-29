#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    count = 0;

    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        count += 1;
#ifdef TRACE_SQRT
        printf("%d %16.15lf\n", count, y);
#endif
    }
    return y;
}

int sqrt_newton_iters(void) {
    return count;
}
