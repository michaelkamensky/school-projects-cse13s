#include <stdio.h>
#include <stdlib.h>

#include "trie.h"
#include "code.h"


TrieNode *trie_node_create(uint16_t index) {
    TrieNode *trie_node = (TrieNode *) calloc(1, sizeof(TrieNode));
    trie_node->code = index;
    return trie_node;
}

void trie_node_delete(TrieNode *n) {
    free(n);
}

TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE); 
}

void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i++) {
        trie_node_delete(root->children[i]);
        root->children[i] = NULL;
    }
}

void trie_delete(TrieNode *n) {
    for (int i = 0; i < ALPHABET; i++) {
        if ( n->children[i] != NULL) {
            trie_delete(n->children[i]);
        }
    }
    trie_reset(n); 
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n->children[sym];
}
