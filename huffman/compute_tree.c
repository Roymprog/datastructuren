#include <stdlib.h>

#include "huffman.h"

tree_t compute_tree(frequency_table_t* freqs) {

    // ... SOME CODE MISSING HERE ...

    return 0;
}

void free_tree(tree_t tree) {
    if (!tree) {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}
