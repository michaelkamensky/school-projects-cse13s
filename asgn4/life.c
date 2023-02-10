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

void pop_un_b(Universe *a, Universe *b) {
    uint32_t rows = uv_rows(a);
    uint32_t cols = uv_cols(a);
    bool cell;
    uint32_t neighbors;
    for (uint32_t i = 0; i < rows; i++) {
        for (uint32_t j = 0; j < cols; j++) {
            cell = uv_get_cell(a, i, j);
            neighbors = uv_census(a, i, j);
            if (cell && (neighbors == 2 || neighbors == 3)) {
                uv_live_cell(b, i, j);
            } else {
                if (neighbors == 3) {
                    uv_live_cell(b, i, j);
                }
            }
        }
    }
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
    int gens = 100;
    
    bool toroidal = false;
    bool ncurses = true;
    //Universe *u = uv_create(20,25, false);
    //uv_delete(u);
    //u = uv_create(0,0,true);
    while ((c = getopt(argc, argv, "atsn:i:o:")) != -1) {
        switch (c) {
        case 't':
            toroidal = true;
            break;
        case 'n':
            gens = (uint32_t) strtoul(optarg, NULL, 10); /* Number of gerations */
            break;
        case 's':
            ncurses = false;
            break;
        case 'i':

            break;
        case '0':
            break;
        case 'a':
            //printf("number of rows is %d number of columns %d\n", uv_rows(u), uv_cols(u));
            //FILE *file = fopen("test.txt", "r");
            //printf("File pointer was created\n");
            //uv_populate(u, file);
            //fclose(file);
            //uv_ncurses(u, 0);
            //uint32_t neigh = uv_census(u, 0, 0);
            //printf("the amount of neighbors is %d\n", neigh);
            //uv_live_cell(u, 19,24);
            //uv_live_cell(u, 0,0);
            //uv_dead_cell(u, 1,1);
            //printf("the cell at 1,1 is %d\n", uv_get_cell(u, 1, 1));
            //printf("the cell at 19,24 is %d\n", uv_get_cell(u, 19, 24));
            //printf("the cell at 0,0 is %d\n", uv_get_cell(u, 0, 0));
            //print_universe(utest);
            break;
        default: usage(argv[0]); exit(-1);
        }
    }
    uint32_t num_rows;
    uint32_t num_cols;
    Universe *a = uv_create(0,0,toroidal);
    FILE *file = fopen("test.txt", "r");
    bool condition = uv_populate(a, file);
    if (!condition) {
        printf("There was an Error unable to poulate the from file\n");
    } else {
        rewind(file);
        fscanf(file, "%d  %d\n", &num_rows, &num_cols);
        Universe *b = uv_create(num_rows, num_cols, toroidal);
        //uv_ncurses(a, 0);
        for (int i = 0; i < gens; i++) {
            pop_un_b(a, b);
            if (ncurses) {
                uv_ncurses(b, 0);
            }
        }
    }
    fclose(file);


    return 0;
}
