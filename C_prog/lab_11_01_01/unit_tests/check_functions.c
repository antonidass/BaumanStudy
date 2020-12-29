#include "unit.h"


START_TEST(test_s_spec_common)
{
    char *src = "aaa";

    char *dst = malloc(sizeof(char) * 4);

    int n = my_snprintf(dst, 4, "%s", src);

    int check = strcmp(src, dst);

    int rc = -1;

    if (n == 3 && !check)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}
END_TEST


START_TEST(test_s_spec_multy)
{
    char *src = "aaa";
    char *src2 = "bbb";
    char *src3 = "333";
    char *src4 = " ";

    char *dst = malloc(sizeof(char) * 40);

    int n = my_snprintf(dst, 11, "%s %s %s %s", src, src2, src3, src4);

    int rc = -1;

    if (n == 13)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}
END_TEST


START_TEST(test_c_spec)
{
    char *dst = malloc(sizeof(char) * 6);

    int n = my_snprintf(dst, 6, "%c %c %c", 'a', '1', '0');

    int rc = -1;
    
    int check = strcmp(dst, "a 1 0");

    if (n == 5 && !check)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}
END_TEST



START_TEST(test_hd_spec)
{
    char *dst = malloc(sizeof(char) * 5);

    int n = my_snprintf(dst, 5, "%hd", 9990);

    int rc = -1;
    
    int check = strcmp(dst, "9990");

    if (n == 4 && !check)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}
END_TEST


START_TEST(test_hd_spec_negative)
{
    char *dst = malloc(sizeof(char) * 6);

    int n = my_snprintf(dst, 6, "%hd", -9990);

    int rc = -1;
    
    int check = strcmp(dst, "-9990");

    if (n == 5 && !check)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}
END_TEST



START_TEST(test_hd_spec_all)
{
    char *dst = malloc(sizeof(char) * 20);

    int n = my_snprintf(dst, 10, "%hd %c %s", -32, 'a', "abc");

    int rc = -1;
    
    int check = strcmp(dst, "-32 a abc");

    if (n == 9 && !check)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);

    free(dst);
}


START_TEST(test_null)
{
    int n = my_snprintf(NULL, 0, "%hd", 32);

    int rc = -1;

    if (n == 2)
        rc = OK;
    
    ck_assert_int_eq(rc, OK);
}



Suite *functions_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_s_spec_common);
    tcase_add_test(tc_pos, test_s_spec_multy);
    tcase_add_test(tc_pos, test_c_spec);
    tcase_add_test(tc_pos, test_hd_spec);
    tcase_add_test(tc_pos, test_hd_spec_negative);
    tcase_add_test(tc_pos, test_hd_spec_all);
    tcase_add_test(tc_pos, test_null);

    suite_add_tcase(s, tc_pos);

    return s;
}
