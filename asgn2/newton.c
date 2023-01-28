#include "mathlib.h"

#include <stdio.h>

int count1 = 0;

double sqrt_newton(double x) {

    double z = 0.0;
    double y = 1.0;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        count1 += 1;
    }
    return y;
}

int sqrt_newtons_iters(void) {
    return count1;
}
