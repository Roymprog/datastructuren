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

    struct node* lhs;
    struct node* rhs;
    struct node* parent;

    int children;
    // ... SOME CODE MISSING HERE ...

};
typedef struct node node;

/* Unique id's for numbering nodes in dot format. */
static int global_node_counter = 0;

/* Helper function: Allocate a new tree node and initialise it with
 * the given parameters. Return a pointer to the new node or NULL on
 * failure. */
static node* make_node(int data) {

    node* node = malloc(sizeof(struct node));

    if (node == NULL) {
        return node;
    }

    node->data = data;
    node->lhs = NULL;
    node->rhs = NULL;
    node->parent = NULL;
    node->children = 0;

    return node;
}

static int print_tree_dot_r(node* root, FILE* dotf) {
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

void tree_dot(struct tree* tree, char* filename) {
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

struct tree* tree_init(int turbo) {
    struct tree* tree = malloc(sizeof(struct tree));

    if ( tree == NULL) {
        return tree;
    }

    tree->root = NULL;

    return tree;
}

_Bool has_children(struct node* node) {
    return node->children > 0;
}

void insert(struct node** current, struct node* new_node, struct node* parent) {
    if (*current == NULL) {
        new_node->parent = parent;
        if (parent != NULL) {
            parent->children++;
        }
        *current = new_node;
        return;
    }
    
    parent = *current;

    if ( new_node->data < (*current)->data ) {
        current = &((*current)->lhs);
    } else {
        current = &((*current)->rhs);
    }

    insert(current, new_node, parent);
}

int tree_insert(struct tree* tree, int data) {
    if ( tree == NULL ) {
        return -1;
    }

    if (tree_find(tree, data) == 1) {
        return 1;
    }

    struct node* node = make_node(data);

    if (node == NULL) {
        tree_cleanup(tree);
        return -1;
    }

    insert(&(tree->root), node, NULL);
    
    return 0;
}

struct node* node_find(struct node* node, int data) {
    if (node == NULL) {
        return NULL;
    }

    if ( data > node->data) {
        node_find(node->rhs, data);
    } else if( data < node->data) {
        node_find(node->lhs, data);
    } else {
        return node;
    }
}

int tree_find(struct tree* tree, int data) {
    return node_find(tree->root, data) != NULL;
}

struct node** max(struct node* node) {
    if ( node == NULL) {
        return NULL;
    }

    while (node->rhs) {
        node = node->rhs;
    }

    return &node;
}

_Bool is_right_child(struct node* n) {
    if (n->parent == NULL) {
        return false;
    }

    return n->data > n->parent->data;
}

// Replaces the node that parent of n points at by node "new"
// depending on whether n is the left child or the right child
void point_parent_to_new(struct node* n, struct node* new) {
    if (is_right_child(n)) {
        n->parent->rhs = new;
    } else {
        n->parent->lhs = new;
    }
}

void swap(struct tree* tree, struct node** n1, struct node** n2) {
    struct node* tmp = (*n1);

    (*n1)->lhs = (*n2)->lhs;
    (*n1)->rhs = (*n2)->rhs;
    (*n1)->parent = (*n2)->parent;
    (*n1)->children = (*n2)->children;

    // corner case where to be swapped is root
    if ((*n1)->parent == NULL) {
        tree->root = *n2;
    } else {
        point_parent_to_new(*n1, *n2);
    }

    (*n2)->lhs = tmp->lhs;
    (*n2)->rhs = tmp->rhs;
    (*n2)->parent = tmp->parent;
    (*n2)->children = tmp->children;

    // n2 is always the right child of its parent
    (*n2)->parent->rhs = *n1;
}

void delete(struct tree* tree, struct node** node)  {
    struct node* n = *node;
    
    if (!has_children(n)) {
        point_parent_to_new(n, NULL);
        free(n);
    } else if (n->lhs) {
        point_parent_to_new(n, n->lhs);
        free(n);
    } else if(n->rhs) {
        point_parent_to_new(n, n->rhs);
        free(n);
    } else {
        struct node** max_left = max(n->lhs);
        swap(tree, node, max_left);
        delete(tree, node);
    }
}

int tree_remove(struct tree* tree, int data) {
    if (tree == NULL || tree_find(tree, data) == 0) {
        return 1;
    }

    struct node* node = node_find(tree->root, data);

    delete(tree, &node);

    return 0;
}

void node_print(struct node* node) {
    if (node == NULL) {
        return;
    }

    node_print(node->lhs);
    printf("%d ", node->data);
    node_print(node->rhs);
}

void tree_print(struct tree* tree) {
    node_print(tree->root);
}

void node_cleanup(struct node* node) {
    if ( node == NULL) {
        return;
    } 

    node_cleanup(node->lhs);
    node_cleanup(node->rhs);

    free(node);
}

void tree_cleanup(struct tree* tree) {
    if ( tree == NULL ) {
        return;
    }
    node_cleanup(tree->root);

    free(tree);
}
