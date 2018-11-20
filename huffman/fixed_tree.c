#include "huffman.h"

tree_t fixed_tree(void) {
    tree_t a = make_tree('a', 0, 0, 0);
    tree_t b = make_tree('b', 0, 0, 0);
    tree_t i = make_tree(0, 0, a, b);
    tree_t c = make_tree('c', 0, 0, 0);
    return make_tree(0, 0, i, c);
}
