#include "quick.h"
#include "shell.h"
#include "stats.h"
#include "heap.h"
#include "batcher.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Prints approximations for pi and e and compares it to libary values.\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -h display program help and usage.\n"
        "    -e runs Eulers apprximation of e\n"
        "    -b runs Bailey-Borwein-Plouffe apprximation of pi\n"
        "    -v runs Vietes apprximation of pi\n"
        "    -m runs Madhava apprximation of pi\n"
        "    -s sets stats mode shows the number iterations for each approximation\n"
        "    -n Runs Newton-Raphson square root approximation test\n"
        "    -a runs all tests\n",
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
    for (int i = 0; i < p_size; i++) {
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
    Stats stats = {};
    int do_quick_sort = 0;
    int do_shell_sort = 0;
    int do_heap_sort = 0;
    int do_batcher_sort = 0;

    while ((c = getopt(argc, argv, "abhqsr:n:p:H")) != -1) {
        switch (c) {
        case 'n':
            size = (uint32_t) strtoul(optarg, NULL, 10); /* Size of Array */
            break;
        case 'q':
            //quick_sort(&stats, array, 6);
            do_quick_sort = 1;
            break;
        case 's':
            do_shell_sort = 1;
            break;
        case 'h':
            do_heap_sort = 1;
            break;
        case 'b':
            do_batcher_sort = 1;
            break;
        case 'r':
            seed = (uint32_t) strtoul(optarg, NULL, 10); /* Deterministic seed */
            break;
        case 'p': p_size = (uint32_t) strtoul(optarg, NULL, 10); break;
        default: usage(argv[0]); exit(-1);
        }
    }
#define TEST
#ifdef TEST
    uint32_t array[10] = { 10, 2, 3, 4, 7, 5, 1, 6, 8, 9 };
    size = 10;
#else
    srandom(seed);
    uint32_t *array = random_arr_gen(size);
#endif
    reset(&stats);
    if (do_quick_sort) {
        printf("Before sort\n");
        print_array(array, size, p_size);
        quick_sort(&stats, array, size);
        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
        reset(&stats);
    }
    if (do_shell_sort) {
        printf("Before sort\n");
        print_array(array, size, p_size);
        shell_sort(&stats, array, size);
        printf("Shell Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
    }
    if (do_heap_sort) {
        printf("Before sort\n");
        print_array(array, size, p_size);
        heap_sort(&stats, array, size);
        printf("Heap Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
    }
    if (do_batcher_sort) {
        printf("Before sort\n");
        print_array(array, size, p_size);
        batcher_sort(&stats, array, size);
        printf("batcher Sort, %u elements, %lu moves, %lu compares\n", size, stats.moves,
            stats.compares);
        print_array(array, size, p_size);
    }

    return 0;
}
