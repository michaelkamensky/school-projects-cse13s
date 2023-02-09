#include "universe.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

void uv_ncurses (Universe *u, uint32_t wait) {
    initscr () ; // Initialize the screen .
    curs_set ( FALSE ) ; // Hide the cursor .
    uint32_t rows = uv_rows(u);
    uint32_t cols = uv_cols(u);
    clear();
    for (uint32_t r = 0; r < rows; r++) {
        for (uint32_t c = 0; c < cols; c++) {
            bool b = uv_get_cell(u, r, c);
            if (b) {
                mvprintw(r, c, "x");
            } else {
                mvprintw(r, c, " ");
            }

        }
    }
    refresh();
    if (wait != 0) {
        sleep(wait);
    } else {
        getch();
    }
    endwin();
#if 0
    for ( int col = 0; col < 40; col += 1) {
        clear () ; // Clear the window .
        mvprintw (ROW , col , "o") ; // Displays "o".
        refresh () ; // Refresh the window .
        usleep ( DELAY ) ; // Sleep for 50000 microseconds .
    }

    endwin () ; // Close the screen .
    return 0;
#endif
}



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
    uv_delete(u);
    u = uv_create(0,0,true);
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
            FILE *file = fopen("test.txt", "r");
            printf("File pointer was created\n");
            uv_populate(u, file);
            fclose(file);
            uv_ncurses(u, 0);
            uint32_t neigh = uv_census(u, 0, 0);
            printf("the amount of neighbors is %d\n", neigh);
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
