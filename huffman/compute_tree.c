#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "huffman.h"

void swap(tree_t* t1, tree_t* t2) {
    tree_t temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

_Bool children_present(frequency_table_t* freqs, int index) {
    if (((*freqs)[index*2 + 1] != NULL) && ((*freqs)[index*2 + 2] != NULL)) {
        return true;
    } else {
        return false;
    }
}

_Bool greater_than_left_child(frequency_table_t* freqs, int index) {
    if ((*freqs)[index]->value >= (*freqs)[index*2 + 1]->value) {
        return true;
    } else {
        return false;
    }
}

_Bool greater_than_right_child(frequency_table_t* freqs, int index) {
    if ((*freqs)[index]->value >= (*freqs)[index*2 + 2]->value) {
        return true;
    } else {
        return false;
    }
}

_Bool greater_than_child(frequency_table_t* freqs, int index) {
    if ( greater_than_left_child(freqs, i) || greater_than_right_child(freqs, i)) {
        return true; 
    } else {
        return false;
    }
}

void heapify(frequency_table_t* freqs, int heap_size) {
    for (int l = (heap_size-1)/2; l != 0; l--) {
        int i = l;
        // tree_t current = (*freqs)[i];
        // tree_t left_child = (*freqs)[i*2 + 1];
        // tree_t right_child = (*freqs)[i*2 + 2];
        while(children_present(freqs, i) && greater_than_child(freqs, i)) {
            int left_value = (*freqs)[i*2 + 1]->value;
            int right_value = (*freqs)[i*2 + 2]->value;         
            if (left_value <= right_value) {
                swap(&(*freqs)[i*2 + 1], &(*freqs)[i]);
                i = i*2 + 1;
            } else {
                swap(&(*freqs)[i*2 + 2], &(*freqs)[i]);
                i = i*2 + 2;
            }
        }
    }
}

tree_t compute_tree(frequency_table_t* freqs) {
    int tree_size = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if ((*freqs)[i] != NULL) {
            (*freqs)[tree_size] = (*freqs)[i];
            tree_size++;
            (*freqs)[i] = NULL;
        }
        // // Loop back over sorted part
        // for (int j = i - 1; j != 0; j--) {
        //     if ((*freqs)[i]->value > (*freqs)[j]->value) {
        //         swap((*freqs)[i]->value, (*freqs)[j + 1]->value);
        //         for (int k = i; k = j + 2; k--) {
        //             swap((*freqs)[k]->value, (*freqs)[k - 1]->value);
        //         }
        //         break;
        //     }
        // }
    }
    
    int last_tree_element_index = tree_size -1;
    heapify(freqs, last_tree_element_index);

    for (int i = 0; i < tree_size; i++) {
        printf("char: %c", (*freqs)[i]->letter);
        printf("\n");
        printf("value: %d", (*freqs)[i]->value);
        printf("\n");
        printf("index: %d", i);
        printf("\n");
        free((*freqs)[i]);
    }

    return 0;
}


void free_tree(tree_t tree) {
    if (!tree) {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}
