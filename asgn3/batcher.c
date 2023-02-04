#include "batcher.h"

#include <math.h>
#include <stdio.h>

int bit_length(uint32_t val) {
    int i;
    for (i = 31; i >= 0; i--) {
        if (val & (1 << i)) {
            return i + 1;
        }
    }
    return 0;
}

static void comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y) {
    //if (arr[x] > arr[y]) {
    if (cmp(stats, arr[x], arr[y]) == 1) {
        swap(stats, &arr[x], &arr[y]);
    }
}

void batcher_sort(Stats *stats, uint32_t *arr, uint32_t n) {
    uint32_t t;
    int32_t p;
    uint32_t q;
    uint32_t r;
    int32_t d;

    if (n == 0) {
        return;
    }
    t = bit_length(n);
    p = 1 << (t - 1);

    while (p > 0) {
        q = 1 << (t - 1);
        r = 0;
        d = p;

        while (d > 0) {
            uint32_t i;
            for (i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, arr, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
}
