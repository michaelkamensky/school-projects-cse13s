
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stats.h"
#include "quick.h"

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

uint32_t* random_arr_gen(uint32_t size) {
    uint32_t *array;
    array = malloc(sizeof(uint32_t) * size);
    uint32_t i;
    for (i = 0; i < size; i++){
        uint32_t r = random();
        r = r & 0x3fffffff;
        array[i] = r;
    }
    return array;
}


int main(int argc, char **argv) {
    int c;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t arr[6] = {13, 3, 27, 42, 5, 80};
    Stats stats = {};
    
    while ((c = getopt(argc, argv, "abhqsr:n:pH")) != -1) {
        switch (c) {
        case 'n':
            size =
            (uint32_t)strtoul(optarg, NULL, 10); /* Size of Array */
      break;
        case 'q': 
	    quick_sort(&stats, arr, 6);
	    break;
        case 'r':
            seed = (uint32_t)strtoul(optarg, NULL, 10); /* Deterministic seed */
            break;

        default: usage(argv[0]); exit(-1);
        }
    }

    srandom(seed);
    uint32_t *array = random_arr_gen(size);
    return 0;
}
