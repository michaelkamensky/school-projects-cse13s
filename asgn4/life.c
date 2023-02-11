#include "universe.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

void uv_ncurses (Universe *u, uint32_t wait) {
    //initscr () ; // Initialize the screen .
    curs_set ( FALSE ) ; // Hide the cursor .
    uint32_t rows = uv_rows(u);
    uint32_t cols = uv_cols(u);
    clear();
    for (uint32_t r = 0; r < rows; r++) {
        for (uint32_t c = 0; c < cols; c++) {
            bool b = uv_get_cell(u, r, c);
            if (b) {
                mvprintw(r, c, "o");
            } else {
                mvprintw(r, c, " ");
            }

        }
    }
    refresh();
    if (wait != 0) {
        usleep(wait);
    } else {
        getch();
    }
    //endwin();
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

void uv_clear_b(Universe *b) {
    uint32_t rows = uv_rows(b);
    uint32_t cols = uv_cols(b);
    for (uint32_t i = 0; i < rows; i++) {
        for(uint32_t j = 0; j < cols; j++) {
            uv_dead_cell(b, i, j);
        }
    }
}
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Runs the game of life\n"
        "\n"
        "USAGE\n"
        "   %s [options] \n"
        "\n"
        "OPTIONS\n"
        "    -t : Specify that the Game of Life is to be played on a toroidal universe.\n"
        "    -s : Silence ncurses.\n"
        "    -n generations : Specify the number of generations that the universe goes through. The default number of generations is 100.\n"
        "    -i input : Specify the input file to read in order to populate the universe. By default the input should be stdin\n"
        "    -o output :  Specify the output file to print the final state of the universe to. By default the output should be stdout.\n"
        "    -h : display program help and usage.\n",
        exec);
}

int main(int argc, char **argv) {
    int c;
    int gens = 100;
    char *in_file_name = NULL;
    char *out_file_name = NULL;
    bool toroidal = false;
    bool ncurses = true;
    while ((c = getopt(argc, argv, "ahtsn:i:o:")) != -1) {
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
            in_file_name = strdup(optarg);
            break;
        case 'o':
            out_file_name = strdup(optarg);
            break;
        default: usage(argv[0]); exit(-1);
        }
    }

    Universe *a = uv_create(0,0,toroidal);
    FILE *in_file;
    if (in_file_name) {
        in_file = fopen(in_file_name, "r");
    } else {
        in_file = stdin;
    }
    bool condition = uv_populate(a, in_file);

    if (in_file_name) {
        fclose(in_file);
    }

    if (!condition) {
        printf("There was an Error unable to poulate the from file\n");
    } else {
        Universe *b = uv_create(uv_rows(a), uv_cols(a), toroidal);

        if (ncurses) {
            initscr();
        }
        for (int i = 0; i < gens; i++) {
            pop_un_b(a, b);
            if (ncurses) {
                uv_ncurses(b, 50000);
            }
            Universe *temp = a;
            a = b;
            b = temp;
            uv_clear_b(b);

        }
        if (ncurses) {
            endwin();
        }
        uv_delete(b);
    }
    
    FILE *out_file;
    if (out_file_name) {
        out_file = fopen(out_file_name, "w");
    } else {
        out_file = stdout;
    }
    uv_print(a, out_file);
    if (out_file_name) {
        fclose(out_file);
    }

    uv_delete(a);
    free(in_file_name);
    free(out_file_name);
    return 0;
}
