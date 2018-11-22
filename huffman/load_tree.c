#include "huffman.h"
#include "stack.h"

tree_t load_tree(char* input) {

    struct stack* stack = stack_init();

    while (*input++) {
        stack_push(stack, *input);
    }
    
    while (stack_peek(stack)) {
        char* c = stack_pop(stack);
        
    }

    return 0;
}
