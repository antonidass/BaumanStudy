#include "unit.h"




START_TEST(test_find_max_elem_in_matrix)
{
    int m = 4, n = 3;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 1;
    matrix[0][1] = 3;
    matrix[0][2] = 5;

    matrix[1][0] = 2;
    matrix[1][1] = 7;
    matrix[1][2] = 3;

    matrix[2][0] = 7;
    matrix[2][1] = 1;
    matrix[2][2] = 2;

    matrix[3][0] = 3;
    matrix[3][1] = 3;
    matrix[3][2] = 3;

    int i, j;

    find_index_max_elem_in_matrix(matrix, m, n, &i, &j);

    int rc = (i == 2 && j == 0) ? 0 : -1;

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
}
END_TEST



START_TEST(test_cut_matrix_cut_row)
{
    int m = 5, n = 3;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 1;
    matrix[0][1] = 3;
    matrix[0][2] = 5;

    matrix[1][0] = 2;
    matrix[1][1] = 7;
    matrix[1][2] = 3;

    matrix[2][0] = 7;
    matrix[2][1] = 1;
    matrix[2][2] = 2;

    matrix[3][0] = 3;
    matrix[3][1] = 3;
    matrix[3][2] = 3;

    matrix[4][0] = 1;
    matrix[4][1] = 3;
    matrix[4][2] = -10;

    cut_matrix(matrix, &m, &n);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {1, 3, 5}, {3, 3, 3}, {1, 3, -10} };
    int m2 = 3, n2 = 3;

    int rc = matrix_cmp(matrix, 3, 3, res_matrix, m2, n2);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
}
END_TEST


START_TEST(test_cut_matrix_cut_column)
{
    int m = 2, n = 3;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 1;
    matrix[0][1] = 7;
    matrix[0][2] = 5;

    matrix[1][0] = 7;
    matrix[1][1] = 2;
    matrix[1][2] = 2;


    cut_matrix(matrix, &m, &n);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {7, 5}, {2, 2} };
    int m2 = 2, n2 = 2;

    int rc = matrix_cmp(matrix, m, n, res_matrix, m2, n2);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
}
END_TEST


START_TEST(test_addition_matrix_common)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 1;
    matrix[0][1] = -3;

    matrix[1][0] = 7;
    matrix[1][1] = -2;

    matrix = reallocate_matrix(matrix, m, 1);
    addition_matrix(matrix, m, 3);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {1, -3, 1}, {7, -2, 7}, {4, -3, 4} };
    int m2 = 3, n2 = 3;

    int rc = matrix_cmp(matrix, 3, 3, res_matrix, m2, n2);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m + 1);
}
END_TEST


START_TEST(test_addition_matrix_small)
{
    int m = 1, n = 1;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = -3;

    matrix = reallocate_matrix(matrix, m, 2);
    addition_matrix(matrix, m, 3);

    int res_matrix[MAX_SIZE][MAX_SIZE]    = { {-3, -3, -3}, {-3, -3, -3}, {-3, -3, -3} };
    int m2 = 3, n2 = 3;

    int rc = matrix_cmp(matrix, 3, 3, res_matrix, m2, n2);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m + 2);
}
END_TEST


START_TEST(test_power_matrix_common)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = -3;
    matrix[0][1] = -2;

    matrix[1][0] = 3;
    matrix[1][1] = -5;

    int **pow_matrix = allocate_matrix(m, m);
    power_matrix(matrix, m, 4, &pow_matrix);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {-375, 352}, {-528, -23} };

    int rc = matrix_cmp(pow_matrix, m, n, res_matrix, m, n);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
    free_matrix(pow_matrix, m);
}
END_TEST



START_TEST(test_power_matrix_zero_power)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = -3;
    matrix[0][1] = -2;

    matrix[1][0] = 3;
    matrix[1][1] = -5;

    int **pow_matrix = allocate_matrix(m, m);
    power_matrix(matrix, m, 0, &pow_matrix);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {1, 0}, {0, 1} };

    int rc = matrix_cmp(pow_matrix, m, n, res_matrix, m, n);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
    free_matrix(pow_matrix, m);
}
END_TEST


START_TEST(test_power_zero_matrix_zero_power)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 0;
    matrix[0][1] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 0;

    int **pow_matrix = allocate_matrix(m, m);
    power_matrix(matrix, m, 0, &pow_matrix);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {1, 0}, {0, 1} };

    int rc = matrix_cmp(pow_matrix, m, n, res_matrix, m, n);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix, m);
    free_matrix(pow_matrix, m);
}
END_TEST



START_TEST(test_power_zero_matrix)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 0;
    matrix[0][1] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 0;

    int **pow_matrix = allocate_matrix(m, m);
    power_matrix(matrix, m, 2, &pow_matrix);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {0, 0}, {0, 0} };

    int rc = matrix_cmp(pow_matrix, m, n, res_matrix, m, n);

    ck_assert_int_eq(rc, OK);

    free_matrix(pow_matrix, m);
    free_matrix(matrix, m);
}
END_TEST



START_TEST(test_power_identity_matrix)
{
    int m = 2, n = 2;
    int **matrix = allocate_matrix(m, n);

    matrix[0][0] = 1;
    matrix[0][1] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 3;

    int **pow_matrix = allocate_matrix(m, m);
    power_matrix(matrix, m, 1, &pow_matrix);

    int res_matrix[MAX_SIZE][MAX_SIZE] = { {1, 0}, {0, 3} };

    int rc = matrix_cmp(pow_matrix, m, n, res_matrix, m, n);

    ck_assert_int_eq(rc, OK);

    free_matrix(pow_matrix, m);
    free_matrix(matrix, m);
}
END_TEST



START_TEST(test_mult_common)
{
    int m1 = 2, n1 = 2;
    int **matrix1 = allocate_matrix(m1, n1);

    matrix1[0][0] = 1;
    matrix1[0][1] = 6;

    matrix1[1][0] = 2;
    matrix1[1][1] = 3;



    int m2 = 2, n2 = 2;
    int **matrix2 = allocate_matrix(m2, n2);

    matrix2[0][0] = -2;
    matrix2[0][1] = -1;

    matrix2[1][0] = 5;
    matrix2[1][1] = 3;

    int **res_matrix = allocate_matrix(m2, n2);

    mult_matrix(matrix1, matrix2, m2, res_matrix);


    int res_matrix_check[MAX_SIZE][MAX_SIZE] = { {28, 17}, {11, 7} };
    int rc = matrix_cmp(res_matrix, m2, n2, res_matrix_check, m2, n2);

    ck_assert_int_eq(rc, OK);

    free_matrix(matrix1, m1);
    free_matrix(matrix2, m2);
    free_matrix(res_matrix, m2);

}
END_TEST




Suite *functions_suite(Suite *s)
{
    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_find_max_elem_in_matrix);
    tcase_add_test(tc_pos, test_cut_matrix_cut_row);
    tcase_add_test(tc_pos, test_cut_matrix_cut_column);
    tcase_add_test(tc_pos, test_addition_matrix_common);
    tcase_add_test(tc_pos, test_addition_matrix_small);
    tcase_add_test(tc_pos, test_power_matrix_common);
    tcase_add_test(tc_pos, test_power_matrix_zero_power);
    tcase_add_test(tc_pos, test_power_zero_matrix_zero_power);
    tcase_add_test(tc_pos, test_power_zero_matrix);
    tcase_add_test(tc_pos, test_power_identity_matrix);
    tcase_add_test(tc_pos, test_mult_common);


    suite_add_tcase(s, tc_pos);

    return s;
}
