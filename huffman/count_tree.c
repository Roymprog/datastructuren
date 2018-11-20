#include "huffman.h"

int count_tree(tree_t node) {
    if (node == 0) {
        return 0;
    }
    return 1 + count_tree(node->left) + count_tree(node->right);
}

