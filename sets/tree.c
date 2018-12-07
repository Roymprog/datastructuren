#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

/* C files can be modified anywhere.
 * So you can change or remove these structs to suit your needs. */
struct tree {
    struct node *root;
};

struct node {
    int data;
    struct node *lhs;
    struct node *rhs;

    int children;
    // ... SOME CODE MISSING HERE ...

};
typedef struct node node;

/* Unique id's for numbering nodes in dot format. */
static int global_node_counter = 0;

/* Helper function: Allocate a new tree node and initialise it with
 * the given parameters. Return a pointer to the new node or NULL on
 * failure. */
static node *make_node(int data) {

    node* node = malloc(sizeof(node));

    if (node == NULL) {
        return node;
    }

    node->data = data;

    return node;
}

static int print_tree_dot_r(node *root, FILE *dotf) {
    int left_id, right_id, my_id = global_node_counter++;

    if (root == NULL) {
        fprintf(dotf, "    %d [shape=point];\n", my_id);
        return my_id;
    }
         
    fprintf(dotf, "    %d [color=%s label=\"%d\"]\n",
            my_id, "black", root->data);

    left_id = print_tree_dot_r(root->lhs, dotf);
    fprintf(dotf, "    %d -> %d [label=\"l\"]\n", my_id, left_id);

    right_id = print_tree_dot_r(root->rhs, dotf);
    fprintf(dotf, "    %d -> %d [label=\"r\"]\n", my_id, right_id);

    return my_id;
}

void tree_dot(struct tree *tree, char *filename) {
    node *root = tree->root;
    global_node_counter = 0;
    FILE *dotf = fopen(filename, "w");
    if (!dotf) {
        printf("error opening file: %s\n", filename);
        exit(1);
    }
    fprintf(dotf, "digraph {\n");
    if (root) {
        print_tree_dot_r(root, dotf);
    }
    fprintf(dotf, "}\n");
}

int tree_check(struct tree *tree) {

    // ... SOME CODE MISSING HERE ...

}

struct tree *tree_init(int turbo) {

    struct tree* tree = malloc(sizeof(struct tree));

    if ( tree == NULL) {
        return tree;
    }

    tree->root = NULL;

    return tree;
}

_Bool has_children(struct node* node) {
    return (node->lhs != NULL) || (node->rhs != NULL);
}

int tree_insert(struct tree *tree, int data) {
    if ( tree == NULL ) {
        return -1;
    }

    if (tree_find(tree, data) == 1) {
        return 1;
    }

    struct node* node = make_node(data);

    if (node == NULL) {
        return -1;
    }

    struct node* node = tree->root;

    while ( has_children(node) ) {
       
    }

    return 0;
}

int tree_find(struct tree *tree, int data) {

    // ... SOME CODE MISSING HERE ...

}

int tree_remove(struct tree *tree, int data) {

    // ... SOME CODE MISSING HERE ...

}

void tree_print(struct tree *tree) {

    // ... SOME CODE MISSING HERE ...

}

void node_cleanup(struct node* node) {
    if ( node == NULL) {
        return;
    }

    node_cleanup(node->lhs);
    node_cleanup(node->rhs);

    free(node);
}

void tree_cleanup(struct tree *tree) {
    if ( tree == NULL ) {
        return;
    }

    node_cleanup(tree->root);

    free(tree);
}
