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

void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < u->cols; i++) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
    free(u);
    u = NULL;
    return;
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
   //int *rows = NULL;
   //int *cols = NULL;
   int first[1];
   int second[1];
   int count = 0;
   while (EOF != fscanf(infile, "%d %d\n", first, second)) {
       printf("> %d %d\n", first[0], second[0]);
       count += 1;
   }
   printf("count is %d\n", count);
   printf("temp print for *u %d\n", uv_rows(u));
   fclose(infile);
   return true;
}

void uv_print(Universe *u, FILE *outfile) {
    fprintf(outfile, "u = %p\n", (void *)u);
}

