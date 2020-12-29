#include "../headers/constants.h"
#include "../headers/functions.h"
#include "../headers/iostream.h"
#include "../headers/macrologger.h"



int main(void)
{
    int m_1, n_1, m_2 = 0, n_2 = 0;
    matrix_t matrix_a = NULL, matrix_b = NULL;

    int res = input_matrix(&matrix_a, &m_1, &n_1);

    res = print_error(res, stderr);
    if (res != OK)
        return res;

    cut_matrix(matrix_a, &m_1, &n_1);


    res = input_matrix(&matrix_b, &m_2, &n_2);

    res = print_error(res, stderr);
    if (res != OK)
    {
        free_matrix(matrix_a, m_1);
        return res;
    }  

    cut_matrix(matrix_b, &m_2, &n_2);


    LOG_DEBUG("m1 = %d  m2 = %d", m_1, m_2);
    if (m_1 < m_2)
    {   
        matrix_a = reallocate_matrix(matrix_a, m_1, m_2 - m_1);
        addition_matrix(matrix_a, m_1, m_2);
        m_1 = m_2;
    }
    else if (m_2 < m_1)
    {
        matrix_b = reallocate_matrix(matrix_b, m_2, m_1 - m_2);
        addition_matrix(matrix_b, m_2, m_1);
        m_2 = m_1;
    }
    
    int power_1 = input_power(), power_2 = input_power();

    if (power_1 < 0 || power_2 < 0)
    {
        fprintf(stderr, ERROR_IN_INPUT_POWER_MSG);
        free_matrix(matrix_a, m_1);
        free_matrix(matrix_b, m_2);
        return ERROR_IN_INPUT_POWER;
    }

    matrix_t res_matrix_a = allocate_matrix(m_1, m_1);
    matrix_t res_matrix_b = allocate_matrix(m_2, m_2);
    matrix_t result = allocate_matrix(m_2, m_2);

    power_matrix(matrix_a, m_1, power_1, &res_matrix_a);
    power_matrix(matrix_b, m_2, power_2, &res_matrix_b);
    mult_matrix(res_matrix_a, res_matrix_b, m_2, result);

    print_matrix(result, m_1, m_2);

    free_matrix(matrix_a, m_1);
    free_matrix(matrix_b, m_2);
    free_matrix(res_matrix_a, m_1);
    free_matrix(res_matrix_b, m_2);
    free_matrix(result, m_2);

    return OK;
}