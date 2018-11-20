#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

tree_t make_tree(char letter, int value, tree_t left, tree_t right) {
    tree_t node = malloc(sizeof(struct node));
    if (0 == node) {
        perror("malloc");
        exit(1);
    }
    node->letter = letter;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}
