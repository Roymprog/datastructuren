#include <stdio.h>
#include "huffman.h"

void encode_data(encoding_table_t* table, char* input_data, int* num_encoded,
                 int* num_printed) {
    for (char *p = input_data; *p; p++) {
        code c = (*table)[(unsigned char)*p];

        (*num_encoded)++;
        (*num_printed) += print_code(c);
    }
}
