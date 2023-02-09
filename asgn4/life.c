#include "universe.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int main(int argc, char **argv) {
    int c;
    Universe *u = uv_create(20,25, false);
    while ((c = getopt(argc, argv, "abhqsr:n:p:H")) != -1) {
        switch (c) {
        case 'n':
            break;
        case 'q':
            break;
        case 's':
            break;
        case 'h':
            break;
        case 'b':
            break;
        case 'a':
            printf("number of rows is %d number of columns %d\n", uv_rows(u), uv_cols(u));
            FILE *file = fopen("101.txt", "r");
            printf("File pointer was created\n");
            printf("res = %d\n", uv_populate(u, file));
            printf("Dump survived \n");
            //uv_live_cell(u, 19,24);
            //uv_live_cell(u, 0,0);
            //uv_dead_cell(u, 1,1);
            //printf("the cell at 1,1 is %d\n", uv_get_cell(u, 1, 1));
            //printf("the cell at 19,24 is %d\n", uv_get_cell(u, 19, 24));
            //printf("the cell at 0,0 is %d\n", uv_get_cell(u, 0, 0));
            //print_universe(utest);
            break;
        case 'r':
            break;
        case 'p':
            break;
        default: usage(argv[0]); exit(-1);
        }
    }

    return 0;
}
