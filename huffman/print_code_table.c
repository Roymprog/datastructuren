#include <stdio.h>
#include "huffman.h"

void print_code_table(encoding_table_t* table) {
    for (int i = 0; i < 256; i++) {
        if ((*table)[i].code_length > 0) {
            printf("%c : ", i);
            print_code((*table)[i]);
            putchar('\n');
        }
    }
}
