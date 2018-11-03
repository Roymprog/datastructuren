#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

struct stack {
    int push_count;
    int pop_count;
    int max_stack_size;
    int size;
    int integers[STACK_SIZE];
};

struct stack *stack_init() {
    struct stack *s = malloc(sizeof(struct stack));
    if (s == NULL) {
        return NULL;
    }

    s->size = 0;
    s->push_count = 0;
    s->pop_count = 0;
    s->max_stack_size = 0;

    return s;
}

void stack_cleanup(struct stack *s) {
    fprintf(stderr, "stats %d %d %d\n", s->push_count, s->pop_count, s->max_stack_size);
    free(s);
}

int stack_push(struct stack *s, int c) {
    if (s->size >= STACK_SIZE) {
        return 1;
    }
    s->integers[s->size] = c;
    s->size++;

    s->push_count++;

    return 0;
}

int stack_pop(struct stack *s) {
    if (stack_empty(s)) {
        return -1;
    }

    /* Check whether current stack is greater than
    max stack size current stack size and update max*/
    if (s->size > s->max_stack_size) {
        s->max_stack_size = s->size;
    }

    // Firest reduce size, then return integer at size's position
    s->size--;

    s->pop_count++;

    return s->integers[s->size];
}

int stack_peek(struct stack *s) {
    if (stack_empty(s)) {
        return -1;
    }

    int top = s->size -1;

    return s->integers[top];
}

int stack_empty(struct stack *s) {
    if (s->size == 0) {
        return 1;
    }

    return 0;
}
