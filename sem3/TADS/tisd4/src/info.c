#include "../headers/info.h"



void print_welcome_info()
{
    printf("\n\nОрганизация по работе со стеком. МАССИВ - стек хранится в виде массива. СПИСОК - стек хранится в виде односвязного списка\n"
    "0 - Выход из программы\n"
    "1 - (МАССИВ) Добавление элементов в стек\n"
    "2 - (МАССИВ) Удаление элементов из стека\n"
    "3 - (МАССИВ) Вывод текущего состояния стека\n"
    "4 - (СПИСОК) Добавление элементов в стек\n"
    "5 - (СПИСОК) Удаление элементов из стека\n"
    "6 - (СПИСОК) Вывод текущего состояния стека\n"
    "7 - Вывод массива адресов освободившихся областей\n"
    "8 - Сравнение скорости добавления и удаления элементов стека\n"
    );

    printf("Выберите пункт: ");
}


int input_available_size(int *capacity)
{
    printf("Введите размер стека (от 1 до 1 000 000 элементов) ");
    int rc = scanf("%d", capacity);

    if (rc != 1 || *capacity <= 0 || *capacity > MAX_STACK_SIZE)
    {
        printf(ERROR_IN_CAPACITY_CHOICE_MSG);
        return ERROR_IN_CAPACITY_CHOICE;
    }

    return OK;
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



int time_counting()
{
    int size;
    printf("Введите размер стека (от 1 до 1 000 000): ");
    int rc = scanf("%d", &size);

    if (rc != 1 || size < 1 || size > 1000000)
    {
        printf("Неверный размер!\n");
        return ERROR_IN_CHOICE;
    }

    list_stack_t *head = NULL;

    uint64_t start, end;    
    
    start = tick();
    rc = input_list_stack(size, &head);
    end = tick();

    printf("\nВремя добавления в стек (СПИСОК) %d элементов = %ld тактов\n", size, end - start);

    array_stack_t *arr_stack = malloc(sizeof(array_stack_t));
    arr_stack->elems_count = -1;

    start = tick();
    generate(arr_stack, size);
    end = tick();

    printf("Время добавления в стек (МАССИВ) %d элементов = %ld тактов\n", size, end - start);
    printf("\n");
    
    arr_of_free_areas *arr_f = malloc(sizeof(arr_of_free_areas));
    arr_f->ind = -1;

    start = tick();
    for (int i = 0; i < size; i++)
    {
        delete_element_in_list_stack(&head, arr_f);
    }
    end = tick();
    printf("Время удаления из стека (СПИСОК) %d элементов = %ld тактов\n", size, end - start);


    start = tick();
    for (int i = 0; i < size; i++)
    {
        delete_element_in_arr_stack(arr_stack);
    }
    end = tick();
    printf("Время удаления из стека (МАССИВ) %d элементов = %ld тактов\n\n", size, end - start);


    printf("Объем занимаемой памяти в случае стека на основе массива = %d байт\n", 8 + 8 * size);
    printf("Объем занимаемой памяти в случае стека на основе спсиска = %d байт\n\n", 20 * size);
    

    return OK;
}