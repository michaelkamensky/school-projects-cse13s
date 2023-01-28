#include "mathlib.h"

#include <stdio.h>

int count = 0;

double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    count = 0;

    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        count += 1;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return count;
}
