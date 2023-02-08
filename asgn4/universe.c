#include "universe.h"

#include <stdio.h>
#include <stdlib.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *universe = (Universe *)calloc(1, sizeof(Universe));
    universe->rows = rows;
    universe->cols = cols;
    universe->toroidal = toroidal;
    bool **m = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r += 1) {
        m[r] = (bool *) calloc(cols, sizeof(bool));
    }
    universe->grid = m;
    return universe;

}

uint32_t uv_rows(struct Universe *u) {
    return u->rows;
}

uint32_t uv_cols(struct Universe *u) {
    return u->cols;
}

void uv_print(Universe *u, FILE *outfile) {
    fprintf(outfile, "u = %p\n", (void *)u);
}

