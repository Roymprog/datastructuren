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

void process_char(struct stack *s, char c) {
    if (isoperator(c)) {
            if ((stack_empty(s) == 0) & (precedence(c) >= precedence((char) stack_peek(s)))) {
                char top = (char) stack_pop(s);
                putchar(top);
                putchar(' ');
            } 
            stack_push(s, c);      
        } else {
            putchar(c);
            putchar(' ');
        }
}

void print_stack(struct stack *s) {
    while (stack_peek(s) != -1) {
        putchar(stack_pop(s));
        putchar(' ');
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    struct stack *s = stack_init();

    for (int i = 0; input[i] != 0; i++) {
        if (input[i] == '(') {
            i++;
            while (input[i] != ')') {
                if (isspace(input[i])) {
                    i++;
                    continue;
                }
                process_char(s, input[i]);
                i++;
            }
            print_stack(s);
        } else if (isspace(input[i])) {
            continue;
        } else {
            process_char(s, input[i]);            
        }
    }

    print_stack(s);

    // ... SOME CODE MISSING HERE ...

    stack_cleanup(s);

    return 0;
}
