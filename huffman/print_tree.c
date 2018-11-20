#include <stdio.h>
#include "huffman.h"

void print_tree(tree_t root) {
    if (root == NULL) {
        return;
    }
    // for all nodes, do;
    print_tree(root->left);
    print_tree(root->right);
    // Print
    if (root->letter) {
        printf("%c", root->letter);
    } else {
        printf("%c", SPECIAL_CHAR);
    }
}
