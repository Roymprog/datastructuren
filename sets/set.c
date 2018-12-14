#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "set.h"
#include "tree.h"

/* Implements a set of integers ordered in a tree based on the implementation
*  in tree.c. For more detailed documentation on function implementation, also
*  see tree.c
*/

struct set {
    struct tree* tree;
};

struct set *set_init(int turbo) {
    struct set* set = malloc(sizeof(struct set));

    if (set == NULL) {
        return NULL;
    }
    
    struct tree* tree = tree_init(turbo);

    if (tree == NULL) {
        free(set);
        return NULL;
    }

    set->tree = tree;

    return set;
}

int set_insert(struct set *s, int num) {

    return tree_insert(s->tree, num);

}

int set_find(struct set *s, int num) {

    return tree_find(s->tree, num);

}

int set_remove(struct set *s, int num) {

    return tree_remove(s->tree, num);

}

void set_cleanup(struct set *s) {

    tree_cleanup(s->tree);
    free(s);

}

void set_print(struct set *s) {

    tree_print(s->tree);

}

int set_verify(struct set *s) {

    return tree_check(s->tree);

}
