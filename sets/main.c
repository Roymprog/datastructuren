#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "set.h"

#define BUF_SIZE 256

/* The program reads input from stdin based and creates a set based on some simple 
*  rules. Each input line is parsed until EOF is reached. The program loads the 
*  parsed input into a tree structure based on the implementation in tree.c. 
*  Integers can be added to the tree by providing a "+ [data]" line. Removing data 
*  is done by a "- [data]" line. All current values in the tree are printed in 
*  order when a line contains "p". Checking whether data is currently in the tree 
*  can be done by an input line of "? [data]"
*/

void exit_failure(char *buf, struct set *s) {
    if (s) {
        set_cleanup(s);
    }
    free(buf);
    exit(EXIT_FAILURE);
}

int main(void) {
    // Allocate buffer for line input
    char *buf = malloc(BUF_SIZE);
    if (!buf) {
        perror("Could not allocate input buffer");
        return EXIT_FAILURE;
    }

    // Initialize set and deal with malloc failure
    struct set *s = set_init(0);

    if ( s == NULL ) {
        free(buf);
        return EXIT_FAILURE;
    }

    // Read input till EOF is reached
    while (fgets(buf, BUF_SIZE, stdin)) {
        char *endptr;
        char *command;
        char *num_str;
        int num;
        
        command = strtok(buf, " ");  // get command: +,-,?,p
        if (strchr("+-?", *command)) { // operation with operand
            num_str = strtok(NULL, "\n");
            if (!num_str) {
                printf("set operation '%c' requires integer operand\n",
                        *command);
                exit_failure(buf, s);
            }
            num = (int) strtol(num_str, &endptr, 10);
            if (*endptr != '\0') {
                printf("error converting '%s' to an integer\n", num_str);
                exit_failure(buf, s);
            }
        }

        // Deal with operators
        switch (*command) {
            case '+':
                if( set_insert(s, num) == -1) {
                    exit_failure(buf, s);
                }
                break;

            case '-':
                set_remove(s,num);
                break;

            case 'p':
                set_print(s);
                break;

            case '?':
                if (set_find(s, num) == 0) {
                    printf("not found: %d\n", num);
                } else {
                    printf("found: %d\n", num);
                }
                break;        
        }
    }

    if ( set_verify(s) == 1 ) { // Debug function
        fprintf(stderr, "Set implementation failed verification!\n");
    }

    // Clean up properly after success;
    free(buf);
    set_cleanup(s);

    return EXIT_SUCCESS;
}
