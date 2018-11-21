#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void set_table_node(encoding_table_t* table, tree_t node, int value, int bin_value, int length) {
    if (node == NULL) {
        return;
    }

    // Store each character in its corresponding ASCII value slot in table
    int index = (int) node->letter;
    
    if ((node->left == NULL) && (node->right == NULL)) {
        // Fill table node
        code entry;
        entry.letter = node->letter;
        entry.bin_encoding = bin_value;
        entry.encoding = value;
        entry.code_length = length;
        (*table)[index] = entry;
    }

    // Increase length
    length++;
    // Binary shift for left node
    value = value*2;
    bin_value = bin_value*10;
    set_table_node(table, node->left, value, bin_value, length);
    // Binary shift for right node
    value++;
    bin_value++;
    set_table_node(table, node->right, value, bin_value, length);
}

encoding_table_t* compute_code_table(tree_t root) {
    encoding_table_t* result = calloc(1, sizeof(encoding_table_t));
    if (result == 0) {
        perror("calloc");
        exit(1);
    }

    set_table_node(result, root->left, 0, 0, 1);
    set_table_node(result, root->right, 1, 1, 1);

    return result;
}

void free_code_table(encoding_table_t* table) {

    // ... SOME CODE MISSING ...

    free(table);
}
