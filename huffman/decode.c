#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

static
char* my_get_line(void) {
    char *line = 0;
    size_t n = 0;
    if (-1 == getline(&line, &n, stdin)) {
        perror("getline");
        free(line);
        exit(1);
    }
    return line;
}

int main(void) {
    char *tree_line = my_get_line();

    tree_t tree = load_tree(tree_line);

    if (tree == 0) {
        free(tree_line);
        return 1;
    }
    
    // Get second output line with encoded characters
    char* encoded = my_get_line();
    // Reference pointer to free memory on cleanup
    char* string = encoded;

    tree_t root = tree;
    while (*encoded != '\0') {
        if ((tree->left == NULL) && (tree->right == NULL)) {
            putchar(tree->letter);
            tree = root;
            continue;
        }
        if (*encoded == '0') {
            tree = tree->left;
        } else if (*encoded == '1') {
            tree = tree->right;
        } 

        encoded = (encoded + 1);

    }

    // Cleanup.
    free(tree_line);
    free(string);
    free_tree(tree);

    return 0;
}
