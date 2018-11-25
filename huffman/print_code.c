#include <stdio.h>
#include "huffman.h"

int print_code(code c) {
	if (c.code_length == 0) {
		return -1;
	}

	// There is at least 1 number in the "binary integer"
	int bin_character_count = 1;
	int number = c.bin_encoding;

	// Rather savage way of counting the amount of characters in "binary integer",
	// loops cuts off last number of "binary integer" each iteration
	while((number = number / 10)) {
		bin_character_count++;
	} 

	int leading_zero_count = c.code_length - bin_character_count;

	for (int i = 0; i < leading_zero_count; i++){
		putchar('0');
	}

	printf("%d", c.bin_encoding);
	return c.encoding;
}

