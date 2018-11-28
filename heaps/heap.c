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
    array_cleanup(h->array, free_func);
    free(h);
    return 0;
}

int prioq_cleanup(prioq *h, void free_func(void*)) {
    heap_cleanup(h, free_func);
}

_Bool has_parent(struct heap* h, int index) {
    return (array_get(h->array, (index - 1)/2) != NULL);
}

_Bool input_not_null(struct heap* h, int index) {
    return (array_get(h->array, index) != NULL && has_parent(h, index));
}

_Bool is_smaller_than_parent(struct heap* h, int index) {
    return (h->compare(array_get(h->array, (index - 1)/2), array_get(h->array, index)) >= 0);
}

static
int heap_insert(struct heap *h, void *p) {
    struct array* array = h->array;
    array_append(array, p);
    long int index = (long int) prioq_size(h) - 1;
    while(index > 0 && input_not_null(h, index) && is_smaller_than_parent(h, index)) {
        void* tmp = array_get(array, (index - 1)/2);
        array_set(array, (index - 1)/2, array_get(array, index));
        array_set(array, index, tmp);
        index = (index - 1) /2;
    }
}

int prioq_insert(prioq *h, void *p) {
    return heap_insert(h, p);
}

_Bool children_present(struct heap* h, int index) {
    return (array_get(h->array, index*2 + 1) != NULL && array_get(h->array, index*2 + 2) != NULL);
}

_Bool greater_than_right_child(struct heap* h, int index) {
    return (h->compare(array_get(h->array, index), array_get(h->array, index*2 + 2)) >= 0);
}

_Bool greater_than_left_child(struct heap* h, int index) {
    return (h->compare(array_get(h->array, index), array_get(h->array, index*2 + 1)) >= 0);
}

_Bool right_child_greater_than_left(struct heap* h, int index) {
    return (h->compare(array_get(h->array, index*2 + 2), array_get(h->array, index*2 + 1)) >= 0);
}

static
void* heap_pop(struct heap *h) {
    struct array* array = h->array;
    int first = 0;
    int last = array_size(array) - 1;

    // Swap first with last
    void* tmp = array_get(array, first);
    array_set(array, first, array_get(array, last));
    array_set(array, last, tmp);

    void* min_element = array_pop(array);

    int i = 0;
    while(children_present(h, i) && (greater_than_right_child(h, i) || greater_than_left_child(h, i) )) {
        if (right_child_greater_than_left(h, i)) {
            void* tmp = array_get(array, i*2 + 1);
            array_set(array, i*2 + 1, array_get(array, i));
            array_set(array, i, tmp);
            i = i*2 + 1;
        } else {
            void* tmp = array_get(array, i*2 + 2);
            array_set(array, i*2 + 2, array_get(array, i));
            array_set(array, i, tmp);
            i = i*2 + 2;
        }
    }

    return min_element;
}

void* prioq_pop(prioq *h) {
    return heap_pop(h);
}
