#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

/* Implements a tree datastructure representing a Binary Search Tree(BST).
*  Expects integers as data and orders them based on their relative value
*/

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

/* Recursively validates the tree. Call this function with a status
*  code of 0. The function will set the status code to 1 if one of the
*  lhs or rhs children is greater or equal, or smaller or equal, respectively
*/
void tree_check_r(struct node* node, int* status_code) {
    if ( node == NULL ) {
        return;
    }

    if ((node->lhs != NULL && node->data <= node->lhs->data) || 
        (node->rhs != NULL && node->data >= node->rhs->data)) {

        *status_code = 1;
    }

    tree_check_r(node->lhs, status_code);
    tree_check_r(node->rhs, status_code);
}

/* Calls the recursive tree check function providing the root
*  of the tree and returns the status_code accordingly
*/
int tree_check(struct tree *tree) {

    int status_code = 0;

    tree_check_r(tree->root, &status_code);

    return status_code;

}

// Initialized tree and checks 
struct tree* tree_init(int turbo) {
    struct tree* tree = malloc(sizeof(struct tree));

    if ( tree == NULL) {
        return tree;
    }

    tree->root = NULL;

    return tree;
}

// Returns true if has children, false if none present
_Bool has_children(struct node* node) {
    return node->children > 0;
}

// Inserts new node recursively
void insert(struct node** current, struct node* new_node, struct node* parent) {
    // Termination step
    if (*current == NULL) {
        new_node->parent = parent;
        if (parent != NULL) {
            parent->children++;
        }
        *current = new_node;
        return;
    }
    
    // Not at bottom of tree yet, move parent a level down
    parent = *current;

    // Move current a level down depending on the children's value
    if ( new_node->data < (*current)->data ) {
        current = &((*current)->lhs);
    } else {
        current = &((*current)->rhs);
    }

    insert(current, new_node, parent);
}

// Inserts data in a node in the tree if data is not yet in tree
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

// Recursively find a node or NULL if not found
struct node* node_find(struct node* node, int data) {
    if (node == NULL) {
        return NULL;
    }

    if ( data > node->data) {
        return node_find(node->rhs, data);
    } else if( data < node->data) {
        return node_find(node->lhs, data);
    } 
    
    return node;
}

// Call recursive node_find function from root of tree
int tree_find(struct tree* tree, int data) {
    return node_find(tree->root, data) != NULL;
}

// Find max value in tree by traversing right all the way down
struct node* max(struct node* node) {
    if ( node == NULL) {
        return NULL;
    }

    while (node->rhs) {
        node = node->rhs;
    }

    return node;
}

// Returns true if node is right child of parent, returns false if left child 
_Bool is_right_child(struct node* n) {
    if (n->parent == NULL) {
        return false;
    }

    return n->data > n->parent->data;
}

/* Replaces the node that parent of n points at by node "new"
* depending on whether n is the left child or the right child
*/
void set_parent_pointer(struct node* n, struct node* new) {
    if (is_right_child(n)) {
        n->parent->rhs = new;
    } else {
        n->parent->lhs = new;
    }
}

// Swaps data of two nodes
void swap_data(struct node* n1, struct node* n2) {
    int tmp_data = n1->data;
    n1->data = n2->data;
    n2->data = tmp_data;
}

/* Deletes the provided node knowing the node is present in tree 
*/
void delete(struct node* n)  {
    if (!has_children(n)) {
        set_parent_pointer(n, NULL);
        free(n);
    } else if (n->lhs) {
        set_parent_pointer(n, n->lhs);
        free(n);
    } else if(n->rhs) {
        set_parent_pointer(n, n->rhs);
        free(n);
    } else {
        // Reduce problem down to one of the above 3 cases,
        // only swap data and delete the node with largest value on lhs
        struct node* max_left = max(n->lhs);
        swap_data(n, max_left);
        delete(max_left);
    }
}

/*Removes node with corresponding data from tree if 
  node with int data is present in tree*/
int tree_remove(struct tree* tree, int data) {
    if (tree == NULL || tree_find(tree, data) == 0) {
        return 1;
    }

    struct node* node = node_find(tree->root, data);

    delete(node);

    return 0;
}

// Prints node data in order
void node_print(struct node* node) {
    if (node == NULL) {
        return;
    }

    node_print(node->lhs);
    printf("%d\n", node->data);
    node_print(node->rhs);
}

// Prints tree in order
void tree_print(struct tree* tree) {
    node_print(tree->root);
}

// Recursively clean up node and children
void node_cleanup(struct node* node) {
    if ( node == NULL) {
        return;
    } 

    node_cleanup(node->lhs);
    node_cleanup(node->rhs);

    free(node);
}

// Recursively cleans up tree from bottom up
void tree_cleanup(struct tree* tree) {
    if ( tree == NULL ) {
        return;
    }
    node_cleanup(tree->root);

    free(tree);
}
