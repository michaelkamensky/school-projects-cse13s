#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

int main(void) {
#if 0
    uint8_t data[][] = {
        {1, 2, 3, 4, 0},
        {1, 2, 3, 5, 0},
        {1, 2, 6, 7, 0},
        {7, 10, 5, 5, 0},
        {7, 5, 0}
    }
#endif
    TrieNode *root = trie_create();
#if 0
    for (int i = 0; i < data; i++) {
        
    }
#endif
    TrieNode *e_1 = trie_node_create(1);
    TrieNode *e_2 = trie_node_create(2);
    TrieNode *e_7 = trie_node_create(3);
    root->children[1] = e_1;
    root->children[2] = e_2;
    root->children[7] = e_7;
    TrieNode *e_1_5 = trie_node_create(4);
    TrieNode *e_1_10 = trie_node_create(5);
    TrieNode *e_2_3 = trie_node_create(6);
    TrieNode *e_2_6 = trie_node_create(7);
    e_1->children[5] = e_1_5;
    e_1->children[10] = e_1_10;
    e_2->children[3] = e_2_3;
    e_2->children[6] = e_2_6;

    trie_delete(root);
    trie_node_delete(root);
}
