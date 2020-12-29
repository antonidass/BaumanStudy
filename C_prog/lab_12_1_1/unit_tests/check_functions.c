#include "unit.h"



START_TEST(test_empty_array_in_key)
{
    int *pb_a = NULL;
    int *pe_a = NULL;
    edges_t edges;

    ck_assert_int_eq(key(pb_a, pe_a, &edges), EMPTY_ARRAY_ERR);
}
END_TEST




START_TEST(test_no_elements_after_filter_first_max_last_min)
{
    int a[] = {999, 211, 1054, -22, 21, -4};
    int *pe_a= &a[6];
    edges_t edges;
    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
}
END_TEST



START_TEST(test_some_similar_element)
{
    int a[] = {1, 1, 1, 1, 1};
    int *pe_a= &a[5];

    edges_t edges;
    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
}
END_TEST


START_TEST(test_no_elements_after_filter_first_min_last_max)
{
    int a[] = {-999, 21221};
    int *pe_a= &a[2];
    edges_t edges;

    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
}
END_TEST


START_TEST(test_one_element)
{
    int a[] = {333};
    int *pe_a= &a[1];
    edges_t edges;

    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
}
END_TEST


START_TEST(test_only_max_els_between)
{
    int a[] = {3, 2, 100, 100, 100, -1, 4, 2, 5};
    int *pe_a= &a[9];
    edges_t edges;

    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_only_min_els_between)
{
    int a[] = {3, 2, -1, -1, -1, -1, -1, -1, -1, 100};
    int *pe_a= &a[10];
    edges_t edges;

    int rc = key(a, pe_a, &edges);

    ck_assert_int_eq(rc, OK);
}
END_TEST




Suite *functions_suite(Suite *s)
{
    TCase *tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_empty_array_in_key);
    tcase_add_test(tc_neg, test_no_elements_after_filter_first_max_last_min);
    tcase_add_test(tc_neg, test_no_elements_after_filter_first_min_last_max);
    tcase_add_test(tc_neg, test_one_element);
    tcase_add_test(tc_neg, test_only_max_els_between);
    tcase_add_test(tc_neg, test_only_min_els_between);
    tcase_add_test(tc_neg, test_some_similar_element);
    suite_add_tcase(s, tc_neg);
    
    TCase *tc_pos = tcase_create("positives");
    suite_add_tcase(s, tc_pos);

    return s;
}
