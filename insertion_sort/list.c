#include "list.h"

struct node {
    // ... SOME CODE MISSING HERE ...
};

struct list {
    // ... SOME CODE MISSING HERE ...
};

struct list* list_init() {
    // ... SOME CODE MISSING HERE ...
}

int list_cleanup(struct list *l) {
    // ... SOME CODE MISSING HERE ...
}

struct node* list_new_node(int num) {
    // ... SOME CODE MISSING HERE ...
}

int list_add(struct list *l, int num) {
    // ... SOME CODE MISSING HERE ...
}

int list_add_back(struct list *l, int num) {
    // ... SOME CODE MISSING HERE ...
}

struct node* list_head(struct list *l) {
    // ... SOME CODE MISSING HERE ...
}

int list_length(struct list *l) {
    // ... SOME CODE MISSING HERE ...
}

int list_node_data(struct node* n) {
    // ... SOME CODE MISSING HERE ...
}

struct node* list_next(struct node* n) {
    // ... SOME CODE MISSING HERE ...
}

struct node* list_prev(struct list* l, struct node* n) {
    // ... SOME CODE MISSING HERE ...
}

int list_unlink_node(struct list* l, struct node* n) {
    // ... SOME CODE MISSING HERE ...
}

void list_free_node(struct node* n) {
    // ... SOME CODE MISSING HERE ...
}

int list_insert_after(struct list* l, struct node* n, struct node* m) {
    // ... SOME CODE MISSING HERE ...
}

int list_insert_before(struct list* l, struct node* n, struct node* m) {
    // ... SOME CODE MISSING HERE ...
}
