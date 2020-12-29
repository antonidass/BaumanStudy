#include "unit.h"



START_TEST(test_sort_common)
{
    int a[] = {4, 2, 1, 5, 5, 23, 2, 1, 6};
    int n1 = 9;

    int b[] = {1, 1, 2, 2, 4, 5, 5, 6, 23};
    int n2 = 9;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_sort_sorted)
{
    int a[] = {1, 2, 3, 4, 5};
    int n1 = 5;

    int b[] = {1, 2, 3, 4, 5};
    int n2 = 5;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_sort_with_negative_numbers)
{
    int a[] = {-31, -532, -13, -654, -5};
    int n1 = 5;

    int b[] = {-654, -532, -31, -13, -5};
    int n2 = 5;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_sort_one_elem)
{
    int a[] = {0};
    int n1 = 1;

    int b[] = {0};
    int n2 = 1;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_sort_reverse_array)
{
    int a[] = {999, 888, 774, 33, 2, 1, 0, -999};
    int n1 = 8;

    int b[] = {-999, 0, 1, 2, 33, 774, 888, 999};
    int n2 = 8;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_sort_equal_array)
{
    int a[] = {2, 2, 2, 2, 2, 2, 2, 2};
    int n1 = 8;

    int b[] = {2, 2, 2, 2, 2, 2, 2, 2};
    int n2 = 8;

    mysort(a, n1, sizeof(int), comp);
    
    int rc = array_cmp(a, n1, b, n2);

    ck_assert_int_eq(rc, OK);
}
END_TEST


Suite *sort_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_common);
    tcase_add_test(tc_pos, test_sort_sorted);
    tcase_add_test(tc_pos, test_sort_with_negative_numbers);
    tcase_add_test(tc_pos, test_sort_one_elem);
    tcase_add_test(tc_pos, test_sort_reverse_array);
    tcase_add_test(tc_pos, test_sort_equal_array);

    suite_add_tcase(s, tc_pos);

    return s;
}