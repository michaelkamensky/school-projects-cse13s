#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"
#include "code.h"

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *word = (Word *) calloc(1, sizeof(Word));
    word->len = len;
    // word->syms= syms;
    word->syms = (uint8_t *) calloc(word->len, sizeof(uint8_t));
    memcpy(word->syms, syms, word->len);
    return word;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *word = (Word *) calloc(1, sizeof(Word));
    word->len = w->len + 1;
    word->syms = (uint8_t *) calloc(word->len, sizeof(uint8_t));
    memcpy(word->syms, w->syms, w->len);
    word->syms[word->len-1] = sym;
    return word;

}

void word_delete(Word *w) {
    free(w->syms);
    free(w);
}

WordTable *wt_create(void) {
    WordTable *wordtable = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    Word *empty = word_create(NULL, 0);
    wordtable[EMPTY_CODE] = empty;
    return wordtable;
}

void wt_reset(WordTable *wt) {
    for (uint32_t i = 2; i < MAX_CODE; i++) {
        // check if the position is not null
        if (wt[i] != NULL) {
            // if not null clears the word
            word_delete(wt[i]);
            wt[i] = NULL;
        }
    }
}
