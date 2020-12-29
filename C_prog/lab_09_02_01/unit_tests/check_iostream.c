#include "unit.h"




START_TEST(test_count_elems)
{
    FILE *input_data = fopen("./data_for_unit_tests/data1.txt", "r");

    int rc = count_elems(input_data);
    ck_assert_int_eq(rc, 9);
    fclose(input_data);
}
END_TEST






Suite *iostream_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_count_elems);

    suite_add_tcase(s, tc_pos);

    return s;
}
