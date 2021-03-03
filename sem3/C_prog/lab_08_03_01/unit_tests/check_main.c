#include "unit.h"

void functions_suite(Suite *s);


int matrix_cmp(int **matrix1, int m1, int n1,  int matrix2[][MAX_SIZE], int m2, int n2)
{
    if (n1 != n2 || m1 != m2)
        return ERROR_IN_LEN;
    
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            if (matrix1[i][j] != matrix2[i][j])
                return ERROR_IN_COMPARE;

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
