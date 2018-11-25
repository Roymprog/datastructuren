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

    // Set correct values for table nodes, binary shift
    int value_left = value*2;
    int value_right = value*2 + 1;

    // Calculate the "binary integer" excluding the leading zeros,
    int bin_value_left = bin_value*10;
    int bin_value_right = bin_value*10 + 1;

    // Increase code_length
    length++;

    set_table_node(table, node->left, value_left, bin_value_left, length);
    set_table_node(table, node->right, value_right, bin_value_right, length);
}

encoding_table_t* compute_code_table(tree_t root) {
    if (root == NULL) {
        return NULL;
    }

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
