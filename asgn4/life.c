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
