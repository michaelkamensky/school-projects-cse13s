#include "universe.h"

#include <stdio.h>
#include <stdlib.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

static Universe *__uv_create(Universe *universe, uint32_t rows, uint32_t cols) {
    universe->rows = rows;
    universe->cols = cols;
    bool **m = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r += 1) {
        m[r] = (bool *) calloc(cols, sizeof(bool));
    }
    universe->grid = m;
    return universe;

}

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *universe = (Universe *)calloc(1, sizeof(Universe));
    universe->toroidal = toroidal;
    return __uv_create(universe, rows, cols);
}

static void __uv_delete(Universe *u) {
    for (uint32_t i = 0; i < u->rows; i++) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
    u->rows = 0;
    u->cols = 0;
}

void uv_delete(Universe *u) {
    __uv_delete(u);
    free(u);
    u = NULL;
}

uint32_t uv_rows(struct Universe *u) {
    return u->rows;
}

uint32_t uv_cols(struct Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r <= u->rows && c >= 0 && c <= u->cols) {
        u->grid[r][c] = true;
    }
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r <= u->rows && c >= 0 && c <= u->cols) {
        u->grid[r][c] = false;
    }
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r <= u->rows && c >= 0 && c <= u->cols) {
        return u->grid[r][c];
    } else {
        return false;
    }
}

bool uv_populate(Universe *u, FILE *infile) {
   rewind(infile);
   uint32_t first;
   uint32_t second;
   int count = 0;
   __uv_delete(u);
   while (EOF != fscanf(infile, "%d %d\n", &first, &second)) {
       if (count == 0) {
           __uv_create(u, first, second);
       } else {
           if (first >= 0 && first <= u->rows && second >= 0 && second <= u->cols) {
                uv_live_cell(u, first, second);
           } else{
                return false;
           }
       }
    count += 1;

   }
   return true;
}

void uv_print(Universe *u, FILE *outfile) {
    fprintf(outfile, "u = %p\n", (void *)u);
}

