#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "stack.h"

// For older versions of the check library
#ifndef ck_assert_ptr_nonnull
#define ck_assert_ptr_nonnull(X) _ck_assert_ptr(X, !=, NULL)
#endif
#ifndef ck_assert_ptr_null
#define ck_assert_ptr_null(X) _ck_assert_ptr(X, ==, NULL)
#endif

/* Tests */
START_TEST (test_stack_init_cleanup)
{
    struct stack *s = stack_init();
    ck_assert_ptr_nonnull(s);
    stack_cleanup(s);
}
END_TEST

START_TEST (test_stack_push)
{
    struct stack *s = stack_init();
    ck_assert_int_eq(stack_push(s, 'x'), 0);
    stack_cleanup(s);
}
END_TEST

START_TEST (test_stack_pop)
{
    struct stack *s = stack_init();
    ck_assert_int_eq(stack_push(s, 'x'), 0);
    ck_assert_int_eq(stack_pop(s), 'x');

    ck_assert_int_eq(stack_push(s, 'y'), 0);
    ck_assert_int_eq(stack_push(s, 'z'), 0);

    ck_assert_int_eq(stack_pop(s), 'z');
    ck_assert_int_eq(stack_pop(s), 'y');
    stack_cleanup(s);
}
END_TEST

START_TEST (test_stack_peek)
{
    struct stack *s = stack_init();
    ck_assert_int_eq(stack_push(s, 'x'), 0);
    ck_assert_int_eq(stack_push(s, 'y'), 0);
    ck_assert_int_eq(stack_push(s, 'z'), 0);

    ck_assert_int_eq(stack_peek(s), 'z');
    ck_assert_int_eq(stack_peek(s), 'z');
    ck_assert_int_eq(stack_pop(s), 'z');

    ck_assert_int_eq(stack_peek(s), 'y');
    ck_assert_int_eq(stack_pop(s), 'y');

    ck_assert_int_eq(stack_peek(s), 'x');
    stack_cleanup(s);
}
END_TEST


START_TEST (test_stack_empty)
{
    struct stack *s = stack_init();
    ck_assert_int_eq(stack_empty(s), 1);
    ck_assert_int_eq(stack_push(s, 'x'), 0);
    ck_assert_int_eq(stack_empty(s), 0);
    stack_cleanup(s);
}
END_TEST

/* STACK_SIZE exposed in header file */
START_TEST (test_stack_limits)
{
    struct stack *s = stack_init();
    int i;
    for (i = 0; i < STACK_SIZE; i++) {
        ck_assert_int_eq(stack_push(s, i), 0);
    }
    ck_assert_int_eq(stack_peek(s), i - 1); // OK
    ck_assert_int_eq(stack_push(s, 'x'), 1); // stack full, should fail.

    for (i = STACK_SIZE - 1; i >= 0; i--) {
        ck_assert_int_eq(stack_pop(s), i);
    }

    ck_assert_int_eq(stack_pop(s), -1); // stack empty, should fail.
    ck_assert_int_eq(stack_peek(s), -1); // stack still empty.
    stack_cleanup(s);
}
END_TEST

/* TODO: test passing NULL, use after free? */

Suite * stack_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Stack");
    /* Core test case */
    tc_core = tcase_create("Core");

	/* Regular tests. */
    tcase_add_test(tc_core, test_stack_init_cleanup);
    tcase_add_test(tc_core, test_stack_push);
    tcase_add_test(tc_core, test_stack_pop);
    tcase_add_test(tc_core, test_stack_peek);
    tcase_add_test(tc_core, test_stack_empty);
    tcase_add_test(tc_core, test_stack_limits);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = stack_suite();
    sr = srunner_create(s);

    // srunner_run_all(sr, CK_NORMAL);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
