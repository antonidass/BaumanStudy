#include "unit.h"


START_TEST(test_check_data)
{

    double a = 13.32, b = 53.2;
    double *pa = &a, *pb = &b;

    int rc = check_data(pa, pb);

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_compare)
{
    object_t a, b;
    a.density = 21.3;
    b.density = 321.2;

    object_t *pa = &a, *pb = &b;

    int rc = compare(pa, pb);

    ck_assert_int_eq(rc, NEGATIVE_NUMBER);
}
END_TEST


Suite *functions_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_check_data);
    tcase_add_test(tc_pos, test_compare);

    suite_add_tcase(s, tc_pos);

    return s;
}
