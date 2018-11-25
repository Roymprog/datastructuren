#include <stdlib.h>
#include "huffman.h"

void swap(tree_t* t1, tree_t* t2) {
    tree_t temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

void insertion_sort(frequency_table_t* freqs, int sorted_length, int tree_size) {
    for (int i = sorted_length; i < tree_size; i++) {
        for (int j = i; j > 0; j--) {
            if ((*freqs)[j]->value < (*freqs)[j - 1]->value) {
                swap(&(*freqs)[j], &(*freqs)[j - 1]);
            }
        }
    }
}

tree_t get_minimun_value_node(frequency_table_t* freqs, int* first_element) {
    tree_t first = (*freqs)[*first_element];
    (*freqs)[*first_element] = NULL;
    *first_element = *first_element + 1;
    return first;
}

tree_t compute_tree(frequency_table_t* freqs) {
    if (*freqs == NULL) {
        return NULL;
    }

    int tree_size = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if ((*freqs)[i] != NULL) {
            (*freqs)[tree_size] = (*freqs)[i];
            tree_size++;
            (*freqs)[i] = NULL;
        }
    }
    
    // The first element in an array is always sorted
    int sorted_length = 1;

    insertion_sort(freqs, sorted_length, tree_size);

    // Define boundaries of sorted array
    int last_element = tree_size - 1;
    int first_element = 0;

    // Combine nodes from sorted array until one element is left, which is the last
    while(first_element != last_element) {
        tree_t first = get_minimun_value_node(freqs, &first_element);
        tree_t second = get_minimun_value_node(freqs, &first_element);

        tree_t new_node = make_tree(SPECIAL_CHAR, first->value + second->value, first, second);
        
        // Insert element in front of sorted array
        first_element--;
        (*freqs)[first_element] = new_node;

        // Sort the array
        for (int i = first_element; i < last_element; i++) {
            if ((*freqs)[i]->value > (*freqs)[i + 1]->value) {
                swap(&(*freqs)[i], &(*freqs)[i + 1]);
            }
        }
    }
    
    return get_minimun_value_node(freqs, &first_element);
}


void free_tree(tree_t tree) {
    if (!tree) {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}
