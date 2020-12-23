#include "../headers/functions.h"






void free_all(matrix_t *matrix, matrix_t *vector, matrix_t *res_matrix, sparse_matrix_t *smatrix, sparse_vector_t *svector, sparse_vector_t *sres)
{
    if (smatrix->pointers != NULL)
        free(smatrix->pointers);
    
    if (smatrix->columns != NULL)
        free(smatrix->columns);

    if (smatrix->values != NULL)
        free(smatrix->values);

    if (svector->values != NULL)
        free(svector->values);

    if (svector->indexes != NULL)
        free(svector->indexes);

    if (sres->indexes != NULL)
        free(sres->indexes);

    if (sres->values != NULL)
        free(sres->values);

    if (res_matrix->matrix != NULL)
        free(res_matrix->matrix);

    if (matrix->matrix != NULL)
        free(matrix->matrix);    

    if (vector->matrix != NULL)
        free(vector->matrix);
}



int main_menu(matrix_t *matrix, matrix_t *vector, matrix_t *res_matrix, sparse_matrix_t *smatrix, sparse_vector_t *svector, sparse_vector_t *sres)
{
    int choice = -1, rc;

    FILE *file = fopen("data.txt", "r");
    read_matrix_from_file(matrix, file);
    fclose(file);
    FILE *file2 = fopen("data2.txt", "r");
    read_vector_from_file(vector, file2);
    fclose(file2);

    parse_matrix(*matrix, smatrix);
    parse_vector(*vector, svector);

    while (choice != 0)
    {
        print_command_info();
        printf("Выберите пункт: ");
        rc = scanf("%d", &choice);
        printf("\n");


        if (rc != 1 || choice < 0)
        {
            printf(ERROR_IN_CHOICE_COMMAND_MSG);
            return ERROR_IN_CHOICE_COMMAND;
        }
        else if (choice == 0)
        {
            return OK;
        }   
        else if (choice == 1)
        {
            FILE *file = fopen("data.txt", "r");
            read_matrix_from_file(matrix, file);
            fclose(file);
            FILE *file2 = fopen("data2.txt", "r");
            read_vector_from_file(vector, file2);
            fclose(file2);

            printf("Матрица и вектор успешно введены !\n");

            parse_matrix(*matrix, smatrix);
            parse_vector(*vector, svector);
        }
        else if (choice == 2)
        {
            rc = input_matrix_from_console(matrix);

            if (rc != OK)
                return rc;
            parse_matrix(*matrix, smatrix);
        }
        else if (choice == 3)
        {
            rc = input_vector_from_console(vector);

            if (rc != OK)
                return rc;
            parse_vector(*vector, svector);
        }
        else if (choice == 4)
        {
            rc = generate(matrix, vector);

            if (rc != OK)
                return rc;

            parse_matrix(*matrix, smatrix);
            parse_vector(*vector, svector);
        }
        else if (choice == 5)
        {  
            if (matrix->column != vector->row)
            {
                printf(ERROR_IN_SIZE_MULT_MSG);
                return ERROR_IN_SIZE_MULT;
            }
            free(sres->values);
            free(sres->indexes);

            int k = (matrix->row > matrix->column) ? matrix->row : matrix->column;
            sres->values = calloc(k, sizeof(int));
            sres->indexes = calloc(k, sizeof(int));
            sres->all_elems_amount = k;

            sparse_mult(smatrix, svector, sres);
            print_sparse_mult_info(*sres);
        }
        else if (choice == 6)
        {
            if (matrix->column != vector->row)
            {
                printf(ERROR_IN_SIZE_MULT_MSG);
                return ERROR_IN_SIZE_MULT;
            }

            res_matrix->column = 1;
            res_matrix->row = matrix->row;
            res_matrix->matrix = allocate_matrix(res_matrix->row, res_matrix->column);
    
            common_mult(matrix, vector, res_matrix);            

            printf("Результат умножения матрицы на вектор: \n");
            print_matrix(*res_matrix);
        }
        else if (choice == 7)
        {   
            counting_time();
        }
        else if (choice == 8)
        {
            int k = (matrix->row > matrix->column) ? matrix->row : matrix->column;
            sres->values = malloc(k * sizeof(int));
            sres->indexes = calloc(k, sizeof(int));
            sres->all_elems_amount = k;
            sparse_mult(smatrix, svector, sres);
            print_all(*matrix, *vector, *sres);
        }
        else if (choice == 9)
        {
            int res = -1;

            printf("Выберите в каком формате выводить матрицу и вектор\n"
                    "1 - разреженный формат\n"
                    "2 - обычный формат\n");

            rc = scanf("%d", &res);

            if (rc != 1 || res > 2 || res < 1)
            {
                printf("Неверно выбран формат!\n");
                return ERROR_IN_FORMAT;
            }

            if (res == 2)
            {
                printf("Исходная матрица\n");
                print_matrix(*matrix);
                printf("\n");
                printf("Исходный вектор\n");
                print_matrix(*vector);
                printf("\n");
            }
            if (res == 1)
            {
                printf("Исходная матрица\n");
                print_sparse_matrix(*smatrix);
                printf("\n");
                printf("Исходный вектор\n");
                print_sparse_vector(*svector);
                printf("\n");
            }
            
        }
        
    }
    return choice;
}




void fill_matrix(matrix_t *matrix, int m, int n, int percent)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (rand() % 100 < percent)
                matrix->matrix[i * n + j] = rand() % 100;
            else
                matrix->matrix[i * n + j] = 0;
        }
    }

}

double get_repeat(int percent, int m, int n)
{
    if ((m >= 100 || n >= 100) && (m <= 800 || n <= 800) && percent >= 40 && percent <= 65)
        return 2.5;

    if ((m >= 100 || n >= 100) && (m <= 800 || n <= 800) && percent >= 40)
    return 0.98;

    if (percent < 36)
        return 40;
    return 10;
}


int generate(matrix_t *matrix, matrix_t *vector)
{
    printf("Введите размер матрицы через пробел (m, n). Размер матрицы не должен превышать 100 элементов ");
    int m, n;
    int rc;

    rc = scanf("%d%d", &m, &n);

    if (rc != 2 || m <= 0 || n <= 0 || m > 100 || n > 100)
    {
        printf(ERROR_IN_SIZE_MATRIX_MSG);
        return ERROR_IN_SIZE_MATRIX;
    }

    printf("Введите процент заполненности матрицы (от 0%% до 100%%) ");

    int percent;

    rc = scanf("%d", &percent);

    if (rc != 1 || percent < 0 || percent > 100)
    {
        printf("Неверный процент заполненности матрицы \n");
        return ERROR_IN_PERCENT;
    }

    free(matrix->matrix);
    free(vector->matrix);

    matrix->row = m;
    matrix->column = n;
    matrix->matrix = allocate_matrix(m, n);

    vector->row = n;
    vector->column = 1;
    vector->matrix = allocate_matrix(m, n);


    fill_matrix(matrix, m, n, percent);
    fill_matrix(vector, n, 1, percent);
    
    return OK;
}


void generate_for_counting(int m, int n, int percent, matrix_t *matrix, matrix_t *vector)
{
    matrix->row = m;
    matrix->column = n;
    matrix->matrix = allocate_matrix(m, n);

    vector->row = n;
    vector->column = 1;
    vector->matrix = allocate_matrix(m, n);

    fill_matrix(matrix, m, n, percent);
    fill_matrix(vector, n, 1, percent);
}




uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}




int counting_time()
{
    matrix_t matrix, vector, res_matrix;
    sparse_matrix_t smatrix;
    sparse_vector_t svector, sres; 

    uint64_t start, end, sum = 0;
    int m, n, percent;

    printf("Введите размер матрицы через пробел. Размер матрицы не превышает 3000x3000 : ");
    int rc = scanf("%d%d", &m, &n);
    
    if (rc != 2 || m > 3000 || n > 3000 || m <= 0 || n <= 0)
        return ERROR_IN_SIZE_MATRIX;

    printf("\nВведите процент заполненности матрицы (от 0 до 100%%) : ");
    rc = scanf("%d", &percent);
    double REPEAT = get_repeat(percent, m, n);
    if (rc != 1 || percent < 0 || percent > 100)
        return ERROR_IN_PERCENT;

    for (int i = 0; i < REPEATS; i++)
    {
        generate_for_counting(m, n, percent, &matrix, &vector);
        res_matrix.column = 1;
        res_matrix.row = matrix.row;
        res_matrix.matrix = allocate_matrix(res_matrix.row, res_matrix.column);

        start = tick();
        common_mult(&matrix, &vector, &res_matrix);
        end = tick();
        sum += (end - start);
    }
    printf("Среднее время умножения матрицы размером %dx%d на вектор в стандартном виде  = %ld тактов\n", m, n, sum / REPEATS);
    sum = 0;

    for (int i = 0; i < REPEATS; i++)
    {
        generate_for_counting(m, n, percent, &matrix, &vector);
        parse_matrix(matrix, &smatrix);
        parse_vector(vector, &svector);
        int k = (m > n) ? m : n;
        sres.values = calloc(k, sizeof(int));
        sres.indexes = malloc(k * sizeof(int));

        start = tick();
        sparse_mult(&smatrix, &svector, &sres);
        end = tick();
        sum += (end - start);
    }
    printf("Среднее время умножения матрицы размером %dx%d на вектор в разреженном виде = %ld тактов\n\n", m, n, (long)(sum / REPEAT));



    printf("Объем используемой памяти при хранении матрицы в стнадратном виде = %d\n", m * n * 4 + 16);
    printf("Объем используемой памяти при хранении матрицы в разреженном виде = %d\n\n", m * n * percent / 100 * 8 + m * 4 + 32);

    free_all(&matrix, &vector, &res_matrix, &smatrix, &svector, &sres);
  
    return OK;
}