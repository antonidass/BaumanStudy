#include "unit.h"



START_TEST(test_parse_num)
{
    list_num_node_t *head = parse_num(3);

    int rc = 0;

    if (head->num != 3 || head->pow != 1)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list_num_node(&head);
}
END_TEST


START_TEST(test_common_mult)
{
    list_num_node_t *first = parse_num(4);
    list_num_node_t *second = parse_num(4);
    list_num_node_t *res = mult_list_numbers(first, second);

    int rc = 0;

    if (res->num != 2 || res->pow != 4)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list_num_node(&first);
    deallocate_list_num_node(&second);
    deallocate_list_num_node(&res);
}
END_TEST


START_TEST(test_diverse_size_mult)
{
    list_num_node_t *first = parse_num(4);
    list_num_node_t *second = parse_num(15);
    list_num_node_t *res = mult_list_numbers(first, second);

    int rc = 0;

    if ((res->num != 2 || res->pow != 2) ||
        (res->next->num != 3 || res->next->pow != 1) || 
        (res->next->next->num != 5 || res->next->next->pow != 1))
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list_num_node(&first);
    deallocate_list_num_node(&second);
    deallocate_list_num_node(&res);
}
END_TEST


START_TEST(test_common_sqr)
{
    list_num_node_t *first = parse_num(4);
    list_num_node_t *res = sqr_list_num(first);

    int rc = 0;

    if (res->num != 2 || res->pow != 4)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list_num_node(&first);
    deallocate_list_num_node(&res);
}
END_TEST



START_TEST(test_get_num_common)
{
    list_num_node_t *first = parse_num(231);
    int num = get_num_from_list_num(first);

    ck_assert_int_eq(num, 231);

    deallocate_list_num_node(&first);
}
END_TEST



Suite *functions_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_parse_num);
    tcase_add_test(tc_pos, test_common_mult);
    tcase_add_test(tc_pos, test_diverse_size_mult);
    tcase_add_test(tc_pos, test_common_sqr);
    tcase_add_test(tc_pos, test_get_num_common);

    suite_add_tcase(s, tc_pos);

    return s;
}
