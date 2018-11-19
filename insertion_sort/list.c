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
    node* n = l->head;
    l->head = NULL;
    l->tail = NULL;
    
    if (n == NULL) {
        free(l);
        return 0;
    }

    do {
        printf("Cleaning up node with number %d", n->number);
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
        return 1;
    }

    if (l->head == NULL) {
        l->tail = new_node;
        l->head = new_node;
        return 0;
    } else {
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
        return 0;
    }
}

int list_add_back(list *l, int num) {
    node* new_node = list_new_node(num);
    if (new_node == NULL) {
        return 1;
    }
    
    if (l->head == NULL) {
        l->tail = new_node;
        l->head = new_node;
        return 0;
    } else {
        new_node->prev = l->tail;
        l->tail->next = new_node;
        l->tail = new_node;
        return 0;
    }
}

node* list_head(list *l) {
    return l->head;
}

int list_length(list *l) {
    int counter = 0;

    for(node *n = l->head; n != NULL; n = n->next) {
        counter++;
    }

    return counter;
}

int list_node_data(node* n) {
    if (n == NULL) {
        return -1;
    }

    return n->number;
}

node* list_next(node* n) {
    if (n == NULL) {
        return n;
    }

    return n->next;
}

node* list_prev(list* l, node* n) {
    if (n == NULL || l == NULL) {
        return n;
    }

    return n->prev;
}

int list_unlink_node(list* l, node* n) {
    if (n == NULL || l == NULL) {
        return 1;
    }
    if (n->prev == NULL) {
        l->head = n->next;
        return 0;
    }

    node* previous = n->prev;
    previous->next = n->next;

    return 0;
}

void list_free_node(node* n) {
    if (n == NULL) {
        return;
    }
    
    free(n);
}

int list_insert_after(list* l, node* n, node* m) {
    if (l->head == NULL || n == NULL || m == NULL) {
        return 1;
    }

    node* current = l->head;
    do {
        if (current == m) {
            if (m->next == NULL) {
                l->tail = n;
            }
            n->next = m->next;
            n->prev = m;
            m->next = n;
            return 0;
        }

        current = current->next;
    } while(current != NULL);

    return 1;
}

int list_insert_before(list* l, node* n, node* m) {
    if (l->head == NULL || n == NULL || m == NULL) {
        return 1;
    }

    node* current = l->head;
    do {
        if (current == m) {
            if (m->prev == NULL) {
                l->head = n;
            }
            n->next = m;
            n->prev = m->prev;
            m->prev = n;
            return 0;
        }

        current = current->next;
    } while(current != NULL);

    return 1;
}
