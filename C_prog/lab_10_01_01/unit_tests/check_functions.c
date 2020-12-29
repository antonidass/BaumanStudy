#include "unit.h"



START_TEST(test_reverse)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    int *b = malloc(sizeof(int));
    *b = 2;

    push_back(&head, a);
    push_back(&head, b);
    
    node_t *rev_head = reverse(head);
    node_t *rev_rev_head = reverse(rev_head);

    int rc = lists_cmp(head, rev_rev_head);
    
    ck_assert_int_eq(rc, OK);

    deallocate_list(&rev_rev_head);
    free(a);
    free(b);
}
END_TEST


START_TEST(test_reverse_null)
{
    node_t *head = NULL;
    node_t *rev_head = reverse(head);

    int rc = 0;

    if (rev_head != NULL)
        rc = 1;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_reverse_one_element)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;

    push_back(&head, a);

    node_t *rev_head = reverse(head);

    int rc = 0;

    if (rev_head->data != head->data)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head);
    free(a);
}
END_TEST


START_TEST(test_pop_back)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    
    push_back(&head, a);
    
    void *data = pop_back(&head);
    
    int rc = 0;

    if (data != a)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    free(a);
}
END_TEST

START_TEST(test_pop_free)
{
    node_t *head = NULL;

    void *data = pop_back(&head);
    
    int rc = 0;

    if (data != NULL)
        rc = 1;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_pop_back_two_elems)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    
    int *b = malloc(sizeof(int));
    *b = 1;
    
    push_back(&head, a);
    push_back(&head, b);
    
    void *data = pop_back(&head);
    
    int rc = 0;

    if (data != b)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head);
    free(a);
    free(b);
}
END_TEST


START_TEST(test_sort)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    
    int *b = malloc(sizeof(int));
    *b = 1;

    int *c = malloc(sizeof(int));
    *c = 311;
    
    push_back(&head, a);
    push_back(&head, b);
    push_back(&head, c);
    
    node_t *sorted_head = sort(head, comp);

    node_t *head_b = NULL;
    push_back(&head_b, b);
    push_back(&head_b, a);
    push_back(&head_b, c);


    int rc = lists_cmp(head_b, sorted_head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&sorted_head);
    deallocate_list(&head_b);
    free(a);
    free(b);
    free(c);
}
END_TEST



START_TEST(test_sort_one_elem)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    
    push_back(&head, a);
    
    node_t *sorted_head = sort(head, comp);

    node_t *head_b = NULL;
    push_back(&head_b, a);

    int rc = lists_cmp(head_b, sorted_head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&sorted_head);
    deallocate_list(&head_b);
    free(a);
}
END_TEST


START_TEST(test_insert_in_head)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    int *b = malloc(sizeof(int));
    *b = 3;
    
    node_t *elem = allocate_node(b);

    push_back(&head, a);
    
    insert(&head, elem, head);

    node_t *head_b = NULL;
    push_back(&head_b, b);
    push_back(&head_b, a);


    int rc = lists_cmp(head_b, head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head_b);
    deallocate_list(&head);
    free(a);
    free(b);
}
END_TEST


START_TEST(test_insert_free)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    int *b = malloc(sizeof(int));
    *b = 3;
    
    node_t *elem = allocate_node(b);

    push_back(&head, a);
    
    insert(&head, elem, NULL);

    node_t *head_b = NULL;
    push_back(&head_b, a);


    int rc = lists_cmp(head_b, head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head_b);
    deallocate_list(&head);
    free(elem);
    free(a);
    free(b);
}
END_TEST


START_TEST(test_insert_not_existed)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    int *b = malloc(sizeof(int));
    *b = 3;
    int *c = malloc(sizeof(int));
    *c = 21;

    node_t *elem = allocate_node(b);
    node_t *before = allocate_node(c);

    push_back(&head, a);
    
    insert(&head, elem, before);

    int rc = 0;
    if (head->next)
        rc = 1;

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head);
    free(elem);
    free(before);
    free(a);
    free(b);
    free(c);
}
END_TEST

START_TEST(test_insert_common)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    int *b = malloc(sizeof(int));
    *b = 3;
    int *c = malloc(sizeof(int));
    *c = 32;
    
    node_t *elem = allocate_node(b);

    push_back(&head, a);
    push_back(&head, c);
    
    insert(&head, elem, head->next);

    node_t *head_b = NULL;
    push_back(&head_b, a);
    push_back(&head_b, b);
    push_back(&head_b, c);


    int rc = lists_cmp(head_b, head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&head_b);
    deallocate_list(&head);
    free(a);
    free(b);
    free(c);
}
END_TEST

START_TEST(test_sort_even_elems)
{
    node_t *head = NULL;

    int *a = malloc(sizeof(int));
    *a = 6;
    
    int *b = malloc(sizeof(int));
    *b = 1;

    int *c = malloc(sizeof(int));
    *c = 311;

    int *d = malloc(sizeof(int));
    *d = 111;
    
    push_back(&head, a);
    push_back(&head, b);
    push_back(&head, c);
    push_back(&head, d);

    
    node_t *sorted_head = sort(head, comp);

    node_t *head_b = NULL;
    push_back(&head_b, b);
    push_back(&head_b, a);
    push_back(&head_b, d);
    push_back(&head_b, c);


    int rc = lists_cmp(head_b, sorted_head);

    ck_assert_int_eq(rc, OK);

    deallocate_list(&sorted_head);
    deallocate_list(&head_b);
    free(a);
    free(b);
    free(c);
    free(d);
}
END_TEST



Suite *functions_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_reverse);
    tcase_add_test(tc_pos, test_pop_back);
    tcase_add_test(tc_pos, test_pop_back_two_elems);
    tcase_add_test(tc_pos, test_sort);
    tcase_add_test(tc_pos, test_sort_one_elem);
    tcase_add_test(tc_pos, test_sort_even_elems);
    tcase_add_test(tc_pos, test_insert_in_head);
    tcase_add_test(tc_pos, test_insert_common);

    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_insert_free);
    tcase_add_test(tc_neg, test_pop_free);
    tcase_add_test(tc_neg, test_reverse_one_element);
    tcase_add_test(tc_neg, test_reverse_null);
    tcase_add_test(tc_neg, test_insert_not_existed);
    


    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
