#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "array.h"
#include "prioq.h"

static
struct heap* heap_init(int (*compare)(const void*, const void*)) {
    if (compare == NULL) {
        return NULL;
    }

    // initialize array
    long initial_capacity = 0;
    struct array* array = array_init(initial_capacity);

    // return on failed malloc
    if (array == NULL) {
        return NULL;
    }

    struct heap* heap = malloc(sizeof(struct heap));

    // in case malloc fails clean up array and return 
    if (heap == NULL) {
        array_cleanup(array, NULL);
        return NULL;
    }

    // set heap properties
    heap->array = array;
    heap->compare = compare;

    return heap;
}

struct heap* prioq_init(int (*compare)(const void*, const void*)) {
    return heap_init(compare);
}

long int prioq_size(struct heap *h) {
    return array_size(h->array);
}

static
int heap_cleanup(struct heap *h, void free_func(void*)) {
    if (h == NULL) {
        return 1;
    }
    
    array_cleanup(h->array, free_func);
    free(h);
    return 0;
}

// Returns the theoretical index of parent providing a node index
long int parent_index(long int index) {
    return (index -1)/2;
}

// Returns the theoretical left child index providing a node index
long int left_child_index(long int index) {
    return (index*2 + 1);
}
// Returns the theoretical right child index providing a node index
long int right_child_index(long int index) {
    return (index*2 + 2);
}

int prioq_cleanup(prioq *h, void free_func(void*)) {
    return heap_cleanup(h, free_func);
}

// Returns true if node with index has parent, false if not
_Bool has_parent(long int index) {
    return (index > 0);
}

// Returns true if node at position index is smaller than it's parent
// based on the heap's provided compare function, returns false otherwise
_Bool is_smaller_than_parent(struct heap* h, long int index) {
    return (h->compare(array_get(h->array, index), array_get(h->array, parent_index(index))) < 0);
}

// Swaps the position of nodes at index1 and index2
void swap(struct heap* h, long int index1, long int index2) {
    struct array* array = h->array;
    void* tmp = array_get(array, index1);
    array_set(array, index1, array_get(array, index2));
    array_set(array, index2, tmp);
}

static
int heap_insert(struct heap *h, void *p) {
    if (p == NULL) {
        return -1;
    }

    struct array* array = h->array;
    array_append(array, p);
    long int index = (long int) prioq_size(h) - 1;

    while(has_parent(index) && is_smaller_than_parent(h, index)) {
        swap(h, index, parent_index(index));
        index = parent_index(index);
    }

    return 0;
}

int prioq_insert(prioq *h, void *p) {
    return heap_insert(h, p);
}

// Returns true if node at index is greater than it's right child
// based on the heap's compare function, false otherwise
_Bool greater_than_right_child(struct heap* h, long int index) {
    void* right_child = array_get(h->array, right_child_index(index));

    if (right_child == NULL) {
        return false;
    }

    return (h->compare(array_get(h->array, index), right_child) > 0);
}

// Returns true if node at index is greater than it's left child
// based on the heap's compare function, false otherwise
_Bool greater_than_left_child(struct heap* h, long int index) {
    void* left_child = array_get(h->array, left_child_index(index));

    if (left_child == NULL) {
        return false;
    }

    return (h->compare(array_get(h->array, index), left_child) > 0);
}

// Returns true if right_child node see from index is greater than 
// it's left child based on the heap's compare function, false otherwise
_Bool right_child_greater_than_left(struct heap* h, long int index) {
    void* right_child = array_get(h->array, right_child_index(index));
    void* left_child = array_get(h->array, left_child_index(index));

    return (h->compare(right_child, left_child) > 0);
}

static
void* heap_pop(struct heap *h) {
    struct array* array = h->array;

    if (array_size(array) == 0) {
        return NULL;
    }

    long int first = 0;
    long int last = array_size(array) - 1;

    swap(h, first, last);

    void* min_element = array_pop(array);

    long int i = 0;
    while(greater_than_right_child(h, i) || greater_than_left_child(h, i) ) {
        if ( (right_child_index(i) >= last ) || right_child_greater_than_left(h, i)) {
            swap(h, i, left_child_index(i));
            i = left_child_index(i);
        } else {
            swap(h, i, right_child_index(i));
            i = right_child_index(i);
        }
    }

    return min_element;
}

void* prioq_pop(prioq *h) {
    return heap_pop(h);
}
