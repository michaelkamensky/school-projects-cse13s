#include "batcher.h"
#include <stdio.h>
#include <math.h>

static void comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y) {
    if (arr[x] > arr[y]) {
        swap(stats, &arr[x], &arr[y]);
    }
}

void batcher_sort(Stats *stats, uint32_t *arr, uint32_t n) {
    uint32_t t = n;
    uint32_t p = 1 << (t - 1);

    while (p > 0) {
        printf("the first loop\n");
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            printf("the second loop\n");
            int i;
            for (i = 0; i < (n - d); i++) {
                if (i == r && p == r) {
                    comparator(stats, arr, i, i+d);
                }
            d = q - p;
            q = q >> 1;
            r = p;
            }
        }
    p = p >> 1;
    }
}
