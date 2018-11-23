#include "huffman.h"
#include "stack.h"
#include <stdio.h>

tree_t recursive_load_tree(struct stack* stack) {
    char* top = stack_pop(stack);

    if (top[0] != SPECIAL_CHAR) {
        return make_tree(top[0], 0, NULL, NULL);
    }

    tree_t right = recursive_load_tree(stack);
    tree_t left = recursive_load_tree(stack);

    return make_tree(top[0], 0, left, right);
}

tree_t load_tree(char* input) {

    struct stack* stack = stack_init();

    while ((*input != '\0') && (*input != '\n')) {
        stack_push(stack, input);
        input = (input + 1);
    }

    tree_t root = recursive_load_tree(stack);

    stack_cleanup(stack);

    return root;
}
