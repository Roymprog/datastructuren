#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    struct node* prev;
    int number;
    struct node* next;
} node;

typedef struct list {
    node* head;
    node* tail;
} list;

list* list_init() {
    list* l = malloc(sizeof(list));
    if (l == NULL) {
        return l;
    }

    l->head = NULL;
    l->tail = NULL;

    return l;
}

int list_cleanup(list *l) {
    node* n = l->tail;

    if (n == NULL) {
        free(l);
        return 0;
    }

    do {
        node* temp = n;
        n = n->next;
        free(temp);
    } while(n != NULL);

    free(l);

    return 0;
}

node* list_new_node(int num) {
    node* n = malloc(sizeof(node));
    if (n == NULL) {
        return n;
    }

    n->number = num;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

int list_add(list *l, int num) {
    node* new_node = list_new_node(num);
    if (new_node == NULL) {
        list_cleanup(l);
        return 1;
    }

    if (l->head == NULL) {
        l->tail = new_node;
        l->head = new_node;
        return 0;
    } else {
        l->head->next = new_node;
        new_node->prev = l->head;
        l->head = new_node;
        return 0;
    }
}

int list_add_back(list *l, int num) {
    node* new_node = list_new_node(num);
    if (new_node == NULL) {
        list_cleanup(l);
        return 1;
    }
    
    if (l->head == NULL) {
        l->tail = new_node;
        l->head = new_node;
        return 0;
    } else {
        l->tail->prev = new_node;
        new_node->next = l->tail;
        l->tail = new_node;
        return 0;
    }
}

node* list_head(list *l) {
    // ... SOME CODE MISSING HERE ...
}

int list_length(list *l) {
    int counter = 0;

    for(node *n = l->tail; n != NULL; n = n->next) {
        counter++;
    }

    return counter;
}

int list_node_data(node* n) {
    // ... SOME CODE MISSING HERE ...
}

node* list_next(node* n) {
    // ... SOME CODE MISSING HERE ...
}

node* list_prev(list* l, node* n) {
    // ... SOME CODE MISSING HERE ...
}

int list_unlink_node(list* l, node* n) {
    // ... SOME CODE MISSING HERE ...
}

void list_free_node(node* n) {
    // ... SOME CODE MISSING HERE ...
}

int list_insert_after(list* l, node* n, node* m) {
    // ... SOME CODE MISSING HERE ...
}

int list_insert_before(list* l, node* n, node* m) {
    // ... SOME CODE MISSING HERE ...
}
