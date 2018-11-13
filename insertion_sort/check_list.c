#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "list.h"

// For older versions of the check library
#ifndef ck_assert_ptr_nonnull
#define ck_assert_ptr_nonnull(X) _ck_assert_ptr(X, !=, NULL)
#endif
#ifndef ck_assert_ptr_null
#define ck_assert_ptr_null(X) _ck_assert_ptr(X, ==, NULL)
#endif

/* Tests */

/* test init/cleanup */
START_TEST (test_init)
{
    struct list* l;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test add/length */
START_TEST (test_add)
{
    struct list* l;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    ck_assert_int_eq(list_add(l, 1), 0);
    ck_assert_int_eq(list_length(l), 1);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test add/length */
START_TEST (test_add_back)
{
    struct list* l;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    ck_assert_int_eq(list_add_back(l, 1), 0);
    ck_assert_int_eq(list_length(l), 1);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test print */
START_TEST (test_add_print)
{
    struct list* l;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    ck_assert_int_eq(list_add(l, 1), 0);
    ck_assert_int_eq(list_add_back(l, 2), 0);
    ck_assert_int_eq(list_add(l, 3), 0);
    ck_assert_int_eq(list_length(l), 3);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test 10 adds */
START_TEST (test_add10)
{
    int len = 10;
    struct list* l;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    for (int i = 0; i < len; i++) {
        ck_assert_int_eq(list_add(l, i), 0);
    }
    ck_assert_int_eq(list_length(l), len);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test head/data */
START_TEST (test_head_data)
{
    struct list* l;
    struct node* n;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    ck_assert_int_eq(list_add(l, 123), 0);
    n = list_head(l);
    ck_assert_ptr_nonnull(n);
    ck_assert_int_eq(list_node_data(n), 123);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test next */
START_TEST (test_check_data10)
{
    int len = 10;
    struct list* l;
    struct node* n;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    for (int i = 0; i < len; i++) {
        ck_assert_int_eq(list_add(l, i), 0);
    }
    ck_assert_int_eq(list_length(l), len);
    n = list_head(l);
    for (int i = len - 1; i >= 0; i--) {
        ck_assert_ptr_nonnull(n);
        ck_assert_int_eq(list_node_data(n), i);
        n = list_next(n);
    }
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test moving around */
START_TEST (test_next9_prev9)
{
    int len = 10;
    struct list* l;
    struct node* n;
    l = list_init();
    ck_assert_ptr_nonnull(l);
    for (int i = 0; i < len; i++) { // add 10
        ck_assert_int_eq(list_add(l, i), 0);
    }
    ck_assert_int_eq(list_length(l), len);
    n = list_head(l);
    for (int i = 0; i < len - 1; i++) { // move to tail
        n = list_next(n);
        ck_assert_ptr_nonnull(n);
    }
    for (int i = 0; i < len - 1; i++) { // move back to head
        n = list_prev(l, n);
        ck_assert_ptr_nonnull(n);
    }
    ck_assert_int_eq(list_node_data(n), 9);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test unlink */
START_TEST (test_unlink)
{
    struct list* l;
    struct node* n;
    l = list_init();
    for (int i = 0; i < 3; i++) { // [2 1 0]
        ck_assert_int_eq(list_add(l, i), 0);
    }
    n = list_head(l);
    n = list_next(n);
    ck_assert_int_eq(list_unlink_node(l, n), 0); // 2 0
    ck_assert_int_eq(list_node_data(n), 1);
    list_free_node(n);
    n = list_head(l);
    n = list_next(n);
    ck_assert_int_eq(list_node_data(n), 0);
    ck_assert_int_eq(list_length(l), 2);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test unlink head */
START_TEST (test_unlink_head)
{
    struct list* l;
    struct node* n;
    l = list_init();
    for (int i = 0; i < 3; i++) { // [2 1 0]
        ck_assert_int_eq(list_add(l, i), 0);
    }
    n = list_head(l);
    ck_assert_int_eq(list_unlink_node(l, n), 0); // 2 0
    list_free_node(n);
    ck_assert_int_eq(list_length(l), 2);
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST


/* test unlink tail */
START_TEST (test_unlink_tail)
{
    struct list* l;
    struct node* n;
    l = list_init();
    for (int i = 0; i < 3; i++) { // add 3 items
        ck_assert_int_eq(list_add(l, i), 0);
    }
    n = list_head(l);
    for (int i = 0; i < 2; i++) { // goto tail
        n = list_next(n);
    }
    ck_assert_int_eq(list_length(l), 3);
    ck_assert_int_eq(list_unlink_node(l, n), 0); // unlink tail
    list_free_node(n);
    ck_assert_int_eq(list_length(l), 2);

    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST


/* test insert after */
START_TEST (test_insert_after)
{
    struct list* l;
    struct node* n1;
    struct node* n2;
    l = list_init();
    for (int i = 0; i < 3; i++) { // [2 1 0]
        ck_assert_int_eq(list_add(l, i), 0);
    }
    n1 = list_head(l);
    n2 = list_next(n1);
    list_unlink_node(l, n1);
    ck_assert_int_eq(list_insert_after(l, n1, n2), 0); // 1 2 0
    ck_assert_int_eq(list_length(l), 3);
    int ref[3] = {1, 2, 0};
    int i;
    for (n1 = list_head(l), i = 0; n1; n1 = list_next(n1), i++) {
        ck_assert_int_eq(list_node_data(n1), ref[i]);
    }
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST

/* test insert before */
START_TEST (test_insert_before)
{
    struct list* l;
    struct node* n1;
    struct node* n2;
    l = list_init();
    for (int i = 0; i < 3; i++) { // [2 1 0]
        ck_assert_int_eq(list_add(l, i), 0);
    }
    n1 = list_head(l);
    n2 = list_next(n1);
    list_unlink_node(l, n2);
    ck_assert_int_eq(list_insert_before(l, n2, n1), 0); // 1 2 0
    ck_assert_int_eq(list_length(l), 3);
    int ref[3] = {1, 2, 0};
    int i;
    for (n1 = list_head(l), i = 0; n1; n1 = list_next(n1), i++) {
        ck_assert_int_eq(list_node_data(n1), ref[i]);
    }
    ck_assert_int_eq(list_cleanup(l), 0);
}
END_TEST


Suite * list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("List");
    /* Core test case */
    tc_core = tcase_create("Core");

	/* Regular tests. */
    tcase_add_test(tc_core, test_init);
    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_add_back);
    tcase_add_test(tc_core, test_add_print);
    tcase_add_test(tc_core, test_add10);
    tcase_add_test(tc_core, test_head_data);
    tcase_add_test(tc_core, test_check_data10);
    tcase_add_test(tc_core, test_next9_prev9);
    tcase_add_test(tc_core, test_unlink);
    tcase_add_test(tc_core, test_unlink_head);
    tcase_add_test(tc_core, test_unlink_tail);
    tcase_add_test(tc_core, test_insert_after);
    tcase_add_test(tc_core, test_insert_before);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = list_suite();
    sr = srunner_create(s);

    // srunner_run_all(sr, CK_NORMAL);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
