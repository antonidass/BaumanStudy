#include "unit.h"


START_TEST(test_find_amount_of_elems_common)
{
    FILE *input_data = fopen("./data_for_unit_tests/data1.txt", "r");

    int rc = find_amount_of_elems(input_data);
    ck_assert_int_eq(rc, 14);
    fclose(input_data);
}
END_TEST


START_TEST(test_find_amount_of_elems_empty)
{
    FILE *input_data = fopen("./data_for_unit_tests/data2.txt", "r");

    int rc = find_amount_of_elems(input_data);
    ck_assert_int_eq(rc, 0);
    fclose(input_data);
}
END_TEST


START_TEST(test_find_amount_of_elems_invalid_data)
{
    FILE *input_data = fopen("./data_for_unit_tests/data3.txt", "r");

    int rc = find_amount_of_elems(input_data);
    ck_assert_int_eq(rc, ERROR_IN_INPUT_DATA);
    fclose(input_data);
}
END_TEST


START_TEST(test_read_data_common)
{
    FILE *input_data = fopen("./data_for_unit_tests/data4.txt", "r");

    int a[6];
    int *pa = a;
    int *pb = read_data(input_data, pa);

    ck_assert_int_eq(*(pb-1), 3);

    fclose(input_data);
}
END_TEST



Suite *iostream_suite(Suite *s)
{
    TCase *tc_neg = tcase_create("negatives");    
    tcase_add_test(tc_neg, test_find_amount_of_elems_empty);
    tcase_add_test(tc_neg, test_find_amount_of_elems_invalid_data);
    suite_add_tcase(s, tc_neg);

    TCase *tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_amount_of_elems_common);
    tcase_add_test(tc_pos, test_read_data_common);
    suite_add_tcase(s, tc_pos);

    return s;
}