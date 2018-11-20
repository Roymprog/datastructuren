#include <stdlib.h>
#include <stdio.h>

#define READ_SIZE 80

char *read_data(void) {
    size_t allocated = 0;
    size_t len = 0;
    char *result = 0;
    while (!feof(stdin)) {
        while (len + READ_SIZE >= allocated) {
            allocated = 2 * allocated + 1;
            result = realloc(result, allocated);
            if (0 == result) {
                perror("realloc");
                exit(1);
            }
        }
        len += fread(result + len, 1, READ_SIZE, stdin);
    }
    result[len - 1] = '\0';
    return result;
}
