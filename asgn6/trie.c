#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

//struct TrieNode {
    //TrieNode *children[ALPHABET];
    //uint16_t code;
//};

TrieNode *trie_node_create(uint16_t index) {
    TrieNode *trie_node = (TrieNode *) calloc(1, sizeof(TrieNode));
    trie_node->code = index;
    return trie_node;
}

void trie_node_delete(TrieNode *n) {
    free(n);
}

TrieNode *trie_create(void) {
    TrieNode *initial = trie_node_create(0);
    if (initial->code == 0) {
        return initial;
    } else {
        return NULL;
    }
   
}


