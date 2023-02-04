#include "shell.h"

#include "gaps.h"

#include <stdio.h>

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    uint32_t g;
    for (g = 0; g <= GAPS; ++g) {
        uint32_t i;
        for (i = g; i < length; ++i) {
            uint32_t j = i;
            uint32_t temp = arr[i];
            //while (j >= g && temp < arr[j - g]) {
            while (j >= g && cmp(stats, temp, arr[j - g]) == -1) {
                //arr[j] = arr[j - g];
                arr[j] = move(stats, arr[j - g]);
                j -= g;
            }
            //arr[j] = temp;
            arr[j] = move(stats, temp);
        }
    }
}
