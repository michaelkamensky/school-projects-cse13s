#include "heap.h"
#include <stdio.h>
#include <math.h>

static uint32_t max_child(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && (cmp(stats, arr[right -1], arr[left -1]) == 1)) {
        return right;
    }
    return left;
}

static void fix_heap(Stats *stats,uint32_t *arr, uint32_t first, uint32_t last) {
    int found = 0;
    uint32_t mother = first;
    uint32_t great = max_child(stats, arr, mother, last);
    while ((mother <= last/2) && (!found)) {
        if (cmp(stats, arr[mother - 1], arr[great -1]) == -1) {
            swap(stats, &arr[mother - 1], &arr[great - 1]);
            mother = great;
            great = max_child(stats, arr, mother, last);
        }
        else {
            found = 1;
        }
    } 
}

static void build_heap(Stats *stats, uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t father;
    for (father = last/2; father > first - 1; father--) {
        fix_heap(stats, arr, father, last);
    }
}

void heap_sort(Stats *stats, uint32_t *arr, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, arr, first, last);
    uint32_t leaf;
    for (leaf = last; leaf > first; leaf--) {
        swap(stats, &arr[first - 1], &arr[leaf - 1]);
        fix_heap(stats, arr, first, leaf -1);
    }
}
