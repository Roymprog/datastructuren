#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

// ... SOME CODE MISSING HERE ...
int precedence(char c){
    if (c == 'F') {
        return 1;
    } else if (c == '~') {
        return 2;
    } else if (c == '^') {
        return 3;
    } else if ((c == '*') | (c == '/')) {
        return 4;
    } else if ((c == '+') | (c == '-')) {
        return 5;
    } else {
        return -1;
    }
}

_Bool isoperator(char c) {
    if ((c == 'F') | (c == '~') | (c == '^') | (c == '*') | (c == '/') | (c == '+') | (c == '-')) {
        return true;
    }
    return false;
}    

_Bool is_invalid_character(char c) {
    if (isoperator(c) | isdigit(c) | (c == '(') | (c ==')')) {
        return false;
    } else {
        return true;
    }
}

_Bool is_invalid_input(char *input) {
    int par_open = 0;
    int par_close = 0;
    for (int i = 0; input[i] != 0; i++) {
        char c = input[i];
        if (is_invalid_character(c)) {
            printf("Program was called with invalid character: %c", (char) c);
            return true;
        } 
        if (c == '(') {
            par_open++;
        } else if (c == ')') {
            par_close++;
        }
    }
    if (par_open != par_close) {
        printf("Program was called with invalid input. Opening and closing parenthesis count does not match");
        return true;
    }
    return false;
}

void process_char(struct stack *s, char *input, int index) {
    char c = input[index];
    if (isoperator(c)) {
        if ((stack_empty(s) == 0) & (precedence(c) >= precedence((char) stack_peek(s)))) {
            char top = (char) stack_pop(s);
            putchar(' ');
            putchar(top);
        } 
        stack_push(s, c);      
    } else if (isspace(c) | (c == '(') | (c == ')')) {
        return;
    } else {
        if ((index != 0) & !isdigit(input[index - 1])) {
            putchar(' ');
        }
        putchar(c);
    }
}

void print_stack(struct stack *s) {
    while (stack_peek(s) != -1) {
        putchar(' ');
        putchar(stack_pop(s));
    }
}

int compute_subnotation(char *input, int *i) {
    struct stack *substack = stack_init();
    *i = *i + 1;

    while (input[*i] != ')') {
        if (input[*i] == '(') {
            compute_subnotation(input, i);
        }
        process_char(substack, input, *i);
        *i = *i + 1;
    }
    print_stack(substack);
    free(substack);

    return *i;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    char *input = argv[1];

    if (is_invalid_input(input)) {
        return 1;
    }

    struct stack *s = stack_init();
    
    for (int index = 0; input[index] != 0; index++) {
        if (input[index] == '(') {
            index = compute_subnotation(input, &index);
        } else {
            process_char(s, input, index);            
        }
    }

    print_stack(s);

    // ... SOME CODE MISSING HERE ...

    stack_cleanup(s);

    return 0;
}
