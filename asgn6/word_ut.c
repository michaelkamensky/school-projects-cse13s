#include <stdio.h>
#include <stdlib.h>

#include "word.h"
#include "code.h"

int main(void) {
uint8_t syms[3] = {3, 99, 6};
    Word *w = word_create(syms, 3);
    Word *w1 = word_append_sym(w, 6);
    word_delete(w1);
    word_delete(w);
    return 0;
}
