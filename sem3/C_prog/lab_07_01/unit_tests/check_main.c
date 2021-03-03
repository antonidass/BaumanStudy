#include "unit.h"

void key_suite(Suite *s);
void sort_suite(Suite *s);
void iostream_suite(Suite *s);


int array_cmp(int *array1, int n1, int *array2, int n2)
{
    if (n1 != n2)
        return ERROR_IN_LEN;
    
    for (int i = 0; i < n1; i++)
    {
        if (array1[i] != array2[i])
            return ERROR_IN_SORTING; 
    }

    return OK;
}


Suite *all_suite()
{
    Suite *s = suite_create("all suite");

    key_suite(s);
    sort_suite(s);
    iostream_suite(s);

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