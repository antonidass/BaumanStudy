#include "unit.h"



START_TEST(test_fibonacci)
{
    int arr[100];
    int n = 3;
    fill_fibonacci(arr, n);

    int ans[3] = {1, 1, 2};

    int rc = array_cmp(arr, n, ans, 3);

    ck_assert_int_eq(rc, OK);
}
END_TEST



START_TEST(test_fibonacci_one_elem)
{
    int arr[100];
    int n = 1;
    fill_fibonacci(arr, n);

    int ans[1] = {1};

    int rc = array_cmp(arr, n, ans, 1);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_fill_my_array)
{
    int arr[5] = {0, 1, 2, 1, 4};
    int n = 5;

    int dst[4];
    int ndst;

    fill_myarray(arr, n, dst, &ndst);
    int ans[4] = {0, 1, 2, 4};

    int rc = array_cmp(dst, ndst, ans, 4);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_fill_my_array_one_elem)
{
    int arr[1] = {-3};
    int n = 1;

    int dst[1];
    int ndst;

    fill_myarray(arr, n, dst, &ndst);
    int ans[1] = {-3};

    int rc = array_cmp(dst, ndst, ans, 1);

    ck_assert_int_eq(rc, OK);
}
END_TEST




Suite *functions_suite(Suite *s)
{
    TCase *tc_neg = tcase_create("positives");
    tcase_add_test(tc_neg, test_fibonacci);
    tcase_add_test(tc_neg, test_fibonacci_one_elem);
    tcase_add_test(tc_neg, test_fill_my_array);
    tcase_add_test(tc_neg, test_fill_my_array_one_elem);

    suite_add_tcase(s, tc_neg);
    
    return s;
}
