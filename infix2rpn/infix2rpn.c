#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

// ... SOME CODE MISSING HERE ...

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    struct stack* s = stack_init();

    for (i = 0; input[i] != 0, i++) {
    	
    }
    // ... SOME CODE MISSING HERE ...

    stack_cleanup(s);

    return 0;
}
