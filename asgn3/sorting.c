#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEAP_SORT_ENABLED    1
#define BATCHER_SORT_ENABLED 2
#define SHELL_SORT_ENABLED   3
#define QUICK_SORT_ENABLED   4

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Sorts a random array using four different sorting algorithms\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -a : Employs all sorting algorithms\n"
        "    -h : Enables Heap Sort\n"
        "    -b : Enables Batcher Sort\n"
        "    -s : Enables Shell Sort\n"
        "    -q : Enables Quicksort\n"
        "    -r seed : Set the random seed to seed. The default seed is 13371453\n"
        "    -n size : Set the array size to size. The default size is 100\n"
        "    -p elements : Print out elements number of elements from the array. The default is "
        "100\n"
        "    -H display program help and usage.\n",
        exec);
}

uint32_t *random_arr_gen(uint32_t size) {
    uint32_t *array;
    array = malloc(sizeof(uint32_t) * size);
    uint32_t i;
    for (i = 0; i < size; i++) {
        uint32_t r = random();
        r = r & 0x3fffffff;
        array[i] = r;
    }
    return array;
}

void print_array(uint32_t *arr, uint32_t size, uint32_t p_size) {
    if (size < p_size) {
        p_size = size;
    }
    for (uint32_t i = 0; i < p_size; i++) {
        printf("%13" PRIu32, arr[i]);
        if (i % 5 == 4) {
            printf("\n");
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int c;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t p_size = 100;
    Stats stats;
    Set options;
    options = set_empty();

    while ((c = getopt(argc, argv, "abhqsr:n:p:H")) != -1) {
        switch (c) {
        case 'n':
            size = (uint32_t) strtoul(optarg, NULL, 10); /* Size of Array */
            break;
        case 'q': options = set_insert(options, QUICK_SORT_ENABLED); break;
        case 's': options = set_insert(options, SHELL_SORT_ENABLED); break;
        case 'h': options = set_insert(options, HEAP_SORT_ENABLED); break;
        case 'b': options = set_insert(options, BATCHER_SORT_ENABLED); break;
        case 'a':
            options = set_insert(options, QUICK_SORT_ENABLED);
            options = set_insert(options, SHELL_SORT_ENABLED);
            options = set_insert(options, HEAP_SORT_ENABLED);
            options = set_insert(options, BATCHER_SORT_ENABLED);
            break;
        case 'r':
            seed = (uint32_t) strtoul(optarg, NULL, 10); /* Deterministic seed */
            break;
        case 'p': p_size = (uint32_t) strtoul(optarg, NULL, 10); break;
        default: usage(argv[0]); exit(-1);
        }
    }
//#define TEST
#ifdef TEST
    uint32_t array[10] = { 10, 2, 3, 4, 7, 5, 1, 6, 8, 9 };
    size = 10;
#else
    srandom(seed);
    uint32_t *array0 = random_arr_gen(size);
    uint32_t *array;
#endif
    reset(&stats);
    if (set_member(options, QUICK_SORT_ENABLED)) {
        reset(&stats);
        array = malloc(sizeof(uint32_t) * size);
        memcpy(array, array0, sizeof(uint32_t) * size);
        //printf("Before sort\n");
        //print_array(array, size, p_size);
        quick_sort(&stats, array, size);
        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
        free(array);
    }
    if (set_member(options, SHELL_SORT_ENABLED)) {
        reset(&stats);
        array = malloc(sizeof(uint32_t) * size);
        memcpy(array, array0, sizeof(uint32_t) * size);
        //printf("Before sort\n");
        //print_array(array, size, p_size);
        shell_sort(&stats, array, size);
        printf("Shell Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
        free(array);
    }
    if (set_member(options, HEAP_SORT_ENABLED)) {
        reset(&stats);
        array = malloc(sizeof(uint32_t) * size);
        memcpy(array, array0, sizeof(uint32_t) * size);
        //printf("Before sort\n");
        //print_array(array, size, p_size);
        heap_sort(&stats, array, size);
        printf(
            "Heap Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves, stats.compares);
        print_array(array, size, p_size);
        free(array);
    }
    if (set_member(options, BATCHER_SORT_ENABLED)) {
        reset(&stats);
        array = malloc(sizeof(uint32_t) * size);
        memcpy(array, array0, sizeof(uint32_t) * size);
        //printf("Before sort\n");
        //print_array(array, size, p_size);
        batcher_sort(&stats, array, size);
        printf("Batcher Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
        free(array);
    }

    free(array0);
    return 0;
}
