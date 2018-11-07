#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

// Assumes every capital letter between F and Z in expression is a function 
_Bool is_function(char c) {
    if ((c >= 'F') & (c <= 'Z')) {
        return true;
    }

    return false;
}

_Bool is_binary_operator(char c) {
    if ((c == '*') | (c == '/') | (c == '+') | (c == '-')) {
        return true;
    }

    return false;
}

_Bool is_operator(char c) {
    if ((is_function(c)) | (c == '~') | (c == '^') | is_binary_operator(c)) {
        return true;
    }

    return false;
}    

_Bool is_invalid_character(char c) {
    if (is_operator(c) | isdigit(c) | isspace(c) | (c == '.') | (c == '(') | (c == ')')) {
        return false;
    }

    return true;
}

// Determines operator precedence, higher return value means higher precedence
int precedence(char c){
    if (is_function(c)) {
        return 6;
    } else if (c == '~') {
        return 5;
    } else if (c == '^') {
        return 4;
    } else if ((c == '*') | (c == '/')) {
        return 3;
    } else if ((c == '+') | (c == '-')) {
        return 2;
    } else if (c == '(') {
        return 1;
    } else {
        return -1;
    }
}

// Loops from i to beginning of input to find non-space char
// returns "end of string" i.e. 0 if no non-space found 
char find_prev_nonspace_char(char *input, int i) {
    while (isspace(input[i]) | is_binary_operator(input[i]) | (input[i] == ')')) {
        if (i == 0) {
            return 0;
        }
        i--;
    }

    return input[i];
}

// Loops to end of string to find non-space character
char find_next_nonspace_char(char *input, int i) {
    while (isspace(input[i]) | is_binary_operator(input[i])) {
        i++;
    }

    return input[i];
}

// Returns whether or not a digit or corresponding parenthesis
// is present in front and after binary operators
_Bool invalid_binary_operator_use(char *input, int i) {
    char prev_nonspace = find_prev_nonspace_char(input, i);
    char next_nonspace = find_next_nonspace_char(input, i);
    if (!(isdigit(prev_nonspace) | (prev_nonspace == ')')) | !(isdigit(next_nonspace) | (next_nonspace == '('))) {
        return true;
    }

    return false;
}

_Bool is_invalid_input(char *input) {
    int par_open = 0;
    int par_close = 0;
    int i;
    for (i = 0; input[i] != 0; i++) {
        char c = input[i];
        if (is_invalid_character(c)) {
            printf("Program was called with invalid character: %c", (char) c);
            return true;
        } 
        if (c == '(') {
            par_open++;
        } else if (c == ')') {
            if (find_prev_nonspace_char(input, i) == '(') {
                printf("Program was called with empty parenthesis expression.");
                return true;
            }
            par_close++;
        } else if (is_binary_operator(c)) {          
            if (invalid_binary_operator_use(input, i)) {
                printf("Input contains binary operator %c without corresponding operands.", c);
                return true;
            }
        }
    }
    if (par_open != par_close) {
        printf("Program was called with invalid input. Opening and closing parentheses do not match.");
        return true;
    }

    // Exit on empty input as per Simon's reply in discussion
    // no non-space is found when end-of-word char "0" is matched
    char next_nonspace = find_next_nonspace_char(input, 0);
    if ((i == 0) | (next_nonspace == 0)) {
        printf("Program did not receive any input. ");
        return true;
    }

    return false;
}

void print_stack(struct stack *s) {
    while (!((stack_peek(s) == -1))) {
        char c = (char) stack_pop(s);
        if (c == '(') {
            break;
        }
        putchar(' ');
        putchar(c);
    }
}

void process_char(struct stack *s, char *input, int index) {
    char c = input[index];
    if (is_operator(c)) {
        char top_char = (char) stack_peek(s);

        if ((stack_empty(s) == 0) & (precedence(top_char) >= precedence(c))) {
            char top = (char) stack_pop(s);
            putchar(' ');
            putchar(top);
        } 

        stack_push(s, c);      
    } else if (isspace(c)) {
        return;
    } else if(c == '(') {
        stack_push(s, c);
    } else if(c == ')') {
        print_stack(s);
    } else {
        
        if (index != 0) {
            char former = input[index - 1];
            
            if (!isdigit(former) & !(former == '.')) {
                putchar(' ');
            }
        }

        putchar(c);
    }
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
        process_char(s, input, index);            
    }

    print_stack(s);

    stack_cleanup(s);

    return 0;
}
