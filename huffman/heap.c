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
    if ( greater_than_left_child(freqs, index) || greater_than_right_child(freqs, index)) {
        return true; 
    } else {
        return false;
    }
}

void heapify(frequency_table_t* freqs, int heap_size) {
    for (int l = (heap_size-1)/2; l != 0; l--) {
        int i = l;
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

tree_t remove_min(frequency_table_t* freqs, int* last_heap_element) {
    if ((*freqs)[0] == NULL) {
        return NULL;
    }
    tree_t min = (*freqs)[0];
    (*freqs)[0] = (*freqs)[*last_heap_element];
    *last_heap_element = *last_heap_element - 1;
    int i = 0;
    while(children_present(freqs, i) && (((*freqs)[i] >= (*freqs)[2*i + 1]) || (*(freqs)[i] >= (*freqs)[2*i + 2]) ) ) {
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
    
    return min;
}

void heap_insert(frequency_table_t* freqs, tree_t element, int* last_heap_element) {
    // Add after last tree element
    *last_heap_element = *last_heap_element + 1;
    (*freqs)[*last_heap_element] = element;
    
    int i = *last_heap_element;
    while(i > 0 && ((*freqs)[i] <= (*freqs)[(i - 1)/2])) {
        swap(&(*freqs)[(i - 1)/2], &(*freqs)[i]);
        i = (i - 1)/2;
    }
}

void print_node(tree_t node) {
    printf("char: %c", node->letter);
    printf("\n");
    printf("value: %d", node->value);
    printf("\n");
}