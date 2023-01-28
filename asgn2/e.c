#include "mathlib.h"

#include <stdio.h>

int iterations = 0;

double e(void) {

    double e = 1.0;
    double last = 1.0;
    double k = 1.0;
    while ((last) > EPSILON) {
        last = last * (1.0 / k);
        e += last;
        k += 1.0;
        iterations += 1;
    }
    /*printf("e called\n");*/
    return e;
}

int e_terms(void) {
    return iterations;
}
