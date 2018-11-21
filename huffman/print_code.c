#include <stdio.h>
#include "huffman.h"

int print_code(code c) {
    int non_zeros = 1;
	int number = c.bin_encoding;

	while((number = number / 10)) {
		non_zeros++;
	} 

	int zero_count = c.code_length - non_zeros;

    for (int i = 0; i < zero_count; i++){
		putchar('0');
    }

    printf("%d", c.bin_encoding);
    return c.bin_encoding;
}

