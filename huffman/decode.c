#include <stdio.h>
#include <stdlib.h>

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
        tree = fixed_tree();
    }
    // print_tree(tree);

    // ... SOME CODE MISSING HERE ...

    // Cleanup.
    free(tree_line);
    free_tree(tree);

    return 0;
}
