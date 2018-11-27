#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

static
int heap_insert(struct heap *h, void *p) {
    struct array* array = h->array;
    array_append(array, p);
    long int index = (long int) prioq_size(h);
 
    while((array_get(array, index) != NULL && array_get(array, (index - 1)/2) != NULL) &&
        h->compare(array_get(array, index), array_get(array, (index - 1)/2))) {
        void* tmp = array_get(array, (index - 1)/2);
        array_set(array, (index - 1)/2, array_get(array, index));
        array_set(array, index, tmp);
        index = (index -1) /2;
    }

}

int prioq_insert(prioq *h, void *p) {
    return heap_insert(h, p);
}

static
void* heap_pop(struct heap *h) {
    return array_pop(h->array);
}

void* prioq_pop(prioq *h) {
    return heap_pop(h);
}
