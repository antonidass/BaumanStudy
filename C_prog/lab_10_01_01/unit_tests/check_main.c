#include "unit.h"

void functions_suite(Suite *s);


int lists_cmp(node_t *first, node_t *second)
{
    int n1 = get_count_elems(first);
    int n2 = get_count_elems(second);

    if (n1 != n2)
        return ERROR_IN_LEN;
     
    while (first && second)
    {
        if (comp(first->data, second->data))
            return ERROR_IN_CMP;

        first = first->next;
        second = second->next;
    }

    if (first != second)
        return ERROR_IN_CMP;

    return OK;
}


Suite *all_suite()
{
    Suite *s = suite_create("all suite");

    functions_suite(s);

    return s;
}

int main()
{
    Suite *s = all_suite();
    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    int errors = srunner_ntests_failed(runner);

    srunner_free(runner);

    return errors;
}
