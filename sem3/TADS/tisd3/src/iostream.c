#include "../headers/iostream.h"





int *allocate_matrix(int m, int n)
{
    int *matrix = malloc(sizeof(int) * m * n);

    if (!matrix)
        return NULL;

    return matrix;
}



void print_command_info()
{
    printf("\n\nОперация умножения матрицы на вектор. Матрица и вектор хранятся в разреженном формате\n\n");

    printf("0 - Выход из программы\n"
           "1 - Ввод матрицы и вектора из файла\n"
           "2 - Ввод матрицы вручную\n"
           "3 - Ввод вектора вручную\n"
           "4 - Генерация случайной матрицы и вектора\n"
           "5 - Операция умножения матрицы на вектор (в разреженном виде)\n"
           "6 - Операция умножения матрицы на вектор (в стандартном виде)\n"
           "7 - Сравнение операции умножения по времени и по памяти\n"
           "8 - Вывести матрицу, вектор и результирующую матрицу\n"
           "9 - Вывести исходную матрицу и вектор\n\n");
}


void print_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.column; j++)
        {
            printf("%5d ", matrix.matrix[i * matrix.column + j]);
        }
        printf("\n");
    }
    printf("\n");
}



void print_sparse_matrix(sparse_matrix_t sparse_matrix)
{  
    printf("Значения: ");
    for (int i = 0; i < sparse_matrix.elems_amount; i++)
        printf("%d ", sparse_matrix.values[i]);
    
    printf("\n");


    printf("Номера столбцов: ");
    for (int i = 0; i < sparse_matrix.elems_amount; i++)
        printf("%d ", sparse_matrix.columns[i] + 1);
    
    printf("\n");
    
    printf("Указатели на строки: ");
    for (int i = 0; i < sparse_matrix.row; i++)
        printf("%d ", sparse_matrix.pointers[i] + 1);
    
    printf("\n");   
}



void print_sparse_vector(sparse_vector_t sparse_vector)
{  
    printf("Значения: ");
    for (int i = 0; i < sparse_vector.not_null_elems_amount; i++)
        printf("%d ", sparse_vector.values[i]);
    
    printf("\n");
    
    printf("Индексы строк: ");
    for (int i = 0; i < sparse_vector.all_elems_amount; i++)
    {
        if (sparse_vector.indexes[i] != 0)
            printf("%d ", sparse_vector.indexes[i]);
    }
    
    printf("\n");   
}


int read_matrix_from_file(matrix_t *matrix, FILE *file)
{
    fscanf(file, "%d%d", &matrix->row, &matrix->column);

    matrix->matrix = allocate_matrix(matrix->row, matrix->column);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->column; j++)
            fscanf(file, "%d", &matrix->matrix[matrix->column * i + j]);

    return OK;
}

int read_vector_from_file(matrix_t *vector, FILE *file)
{
    fscanf(file, "%d", &vector->row);
    vector->column = 1;

    vector->matrix = allocate_matrix(vector->row, vector->column);

    for (int i = 0; i < vector->row; i++)
            fscanf(file, "%d", &vector->matrix[i]);

    return OK;
}


int read_matrix_from_console(matrix_t *matrix, int not_null_count)
{
    matrix->matrix = calloc(matrix->row * matrix->column, sizeof(int));
    int rc;
    int i, j;

    for (int k = 0; k < not_null_count; k++)
    {
        printf("Введите строку, столбец и сам элемент через пробел (i, j, x) : ");

        rc = scanf("%d%d", &i, &j);

        if (rc != 2 || i > matrix->row || i <= 0 || j > matrix->column || j <= 0)
            return ERROR_IN_INPUT_ELEMS;

        
        rc = scanf("%d", &matrix->matrix[matrix->column * (i - 1) + j - 1]);
    }

    return OK;
}


int input_vector_from_console(matrix_t *vector)
{
    printf("Введите размер вектора (m). Размер вектора не превышает 1000. : ");
    int rc = scanf("%d", &vector->row);
    
    vector->column = 1;
    if (rc != 1 || vector->row <= 0 || vector->row > 1000)
    {
        printf("Ошибка. Введен неверный размер вектора.\n");
        return ERROR_IN_SIZE_MATRIX;
    }

    printf("Введите количество ненулевых элементов : ");
    int not_null_count;

    rc = scanf("%d", &not_null_count);

    if (rc != 1 || not_null_count < 0 || not_null_count > vector->row * vector->column)
    {
        printf("Неверное количество ненулевых элементов\n");
        return ERROR_IN_SIZE_MATRIX;
    }

    rc = read_matrix_from_console(vector, not_null_count);

    if (rc != OK)
    {
        return rc;
    }

    printf("Вектор успешно введен!\n");
    return OK;
}



int input_matrix_from_console(matrix_t *matrix)
{
    printf("Введите размер матрицы через пробел (m, n). Размер матрицы не превышает 1000x1000. : ");
    int rc = scanf("%d%d", &matrix->row, &matrix->column);

    if (rc != 2 || matrix->row <= 0 || matrix->column <= 0 || matrix->row > 1000 || matrix->column > 1000)
    {
        printf("Ошибка. Введен неверный размер матрицы.\n");
        return ERROR_IN_SIZE_MATRIX;
    }

    printf("Введите количество ненулевых элементов : ");
    int not_null_count;

    rc = scanf("%d", &not_null_count);

    if (rc != 1 || not_null_count < 0 || not_null_count > matrix->row * matrix->column)
    {
        printf("Неверное количество ненулевых элементов\n");
        return ERROR_IN_SIZE_MATRIX;
    }
    
    rc = read_matrix_from_console(matrix, not_null_count);
    


    if (rc != OK)
    {
        printf("Ошибка. Введен неверный элемент матрицы\n");
        return rc;
    }

    printf("Матрица успешно введена!\n");
    return OK;
}




void print_sparse_mult_info(sparse_vector_t svector)
{
    printf("Результат умножения матрицы на вектор : \n");
    print_sparse_vector(svector);
}

void print_all(matrix_t matrix, matrix_t vector, sparse_vector_t svector)
{
    printf("Исходная матрица \n");
    print_matrix(matrix);
    printf("\n");

    printf("Исходный вектор \n");
    print_matrix(vector);
    printf("\n");

    printf("Результирующий вектор\n");
    print_sparse_vector(svector);
    printf("\n");
}
