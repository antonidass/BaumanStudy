#include "unit.h"



START_TEST(test_empty_array_in_key)
{
    int *pb_a = NULL;
    int *pe_a = NULL;
    int *pb_b = NULL;
    int *pe_b = NULL;
    ck_assert_int_eq(key(pb_a, pe_a, &pb_b, &pe_b), EMPTY_ARRAY_ERR);
    free(pb_b);
}
END_TEST


START_TEST(test_common_filter_first_min_last_max)
{
    int a[] = {54, 5, 211, 32, 21, 32, 999, 54, 32, 21};
    int *pe_a= &a[10];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int ans[] = {211, 32, 21, 32};
    int *pe_ans = &ans[4];

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(array_cmp(pb_b, pe_b - pb_b, ans, pe_ans - ans), 0);
    ck_assert_int_eq(rc, OK);
    free(pb_b);
}
END_TEST


START_TEST(test_common_filter_first_max_last_min)
{
    int a[] = {999, 211, 54, 32, 21, -4};
    int *pe_a= &a[6];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int ans[] = {211, 54, 32, 21};
    int *pe_ans = &ans[4];

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(array_cmp(pb_b, pe_b - pb_b, ans, pe_ans - ans), 0);
    ck_assert_int_eq(rc, OK);
    free(pb_b);
}
END_TEST


START_TEST(test_no_elements_after_filter_first_max_last_min)
{
    int a[] = {999, 211, 1054, -22, 21, -4};
    int *pe_a= &a[6];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
    free(pb_b);
}
END_TEST


START_TEST(test_two_maximums_between)
{
    int a[] = {1, 4, 5, 99, 4, 4, 1, 99, 54, -1, 4, 4};
    int *pe_a= &a[12];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int ans[] = {4, 4, 1, 99, 54};
    int *pe_ans = &ans[5];

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(array_cmp(pb_b, pe_b - pb_b, ans, pe_ans - ans), 0);
    ck_assert_int_eq(rc, OK);
    free(pb_b);
}
END_TEST


START_TEST(test_some_similar_element)
{
    int a[] = {1, 1, 1, 1, 1};
    int *pe_a= &a[5];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
    free(pb_b);
}
END_TEST


START_TEST(test_no_elements_after_filter_first_min_last_max)
{
    int a[] = {-999, 21221};
    int *pe_a= &a[2];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
    free(pb_b);
}
END_TEST


START_TEST(test_one_element)
{
    int a[] = {333};
    int *pe_a= &a[1];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, NO_ELEMENTS_BETWEEN_ERROR);
    free(pb_b);
}
END_TEST


START_TEST(test_only_max_els_between)
{
    int a[] = {3, 2, 100, 100, 100, -1, 4, 2, 5};
    int *pe_a= &a[9];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, OK);
    free(pb_b);
}
END_TEST


START_TEST(test_only_min_els_between)
{
    int a[] = {3, 2, -1, -1, -1, -1, -1, -1, -1, 100};
    int *pe_a= &a[10];
    int *pb_b = NULL;
    int *pe_b = NULL;

    int rc = key(a, pe_a, &pb_b, &pe_b);

    ck_assert_int_eq(rc, OK);
    free(pb_b);
}
END_TEST



Suite *key_suite(Suite *s)
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
    tcase_add_test(tc_pos, test_common_filter_first_min_last_max);
    tcase_add_test(tc_pos, test_common_filter_first_max_last_min);
    tcase_add_test(tc_pos, test_two_maximums_between);
    suite_add_tcase(s, tc_pos);

    return s;
}