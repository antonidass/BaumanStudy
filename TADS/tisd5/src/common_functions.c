#include "../headers/common_functions.h"
#include "../headers/array_queue.h"
#include "../headers/list_queue.h"
#include "../headers/handle_list_service.h"

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





int comparison_queue()
{
    int num;
    printf("\nВведите количество элементов очереди (до 1000000) : ");
    int rc = scanf("%d", &num);

    if (rc != 1 || num > 1000000 || num <= 0)
    {
        printf("Неверное количество элементов!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }

    array_queue_t arr_q;
    list_queue_t list_q;

    create_arr_queue(&arr_q, num);
    create_list_queue(&list_q, num);

    uint64_t start, end, sum_list = 0, sum_arr = 0;
    task_t task;

    for (int i = 0; i < num; i++)
    {
        task = generate_task(1);
        start = tick();
        push_arr_queue(&arr_q, task);
        end = tick();
        sum_arr += (end - start);
    }

    for (int i = 0; i < num; i++)
    {
        task = generate_task(1);
        start = tick();
        push_list_queue(&list_q, task);
        end = tick();
        sum_list += (end - start);
    }
    printf("Время измеряется в тактах процессора!\n\n");
    printf("Время добавления элемента в очередь на основе МАССИВА: %lu\n", sum_arr);
    printf("Время добавления элемента в очередь на основе СПИСКА: %lu\n\n", sum_list);

    sum_arr = sum_list = 0;

    for (int i = 0; i < num; i++)
    {
        start = tick();
        pop_arr_queue(&arr_q, &task);
        end = tick();
        sum_arr += (end - start);
    }

    for (int i = 0; i < num; i++)
    {
        start = tick();
        pop_list_queue(&list_q, &task);
        end = tick();
        sum_list += (end - start);
    }

    printf("Время удаления элемента из очереди на основе МАССИВА: %lu\n", sum_arr);
    printf("Время удаления элемента из очереди на основе СПИСКА: %lu\n\n", sum_list);

    int size_arr = 0, size_list = 0;

    size_list = 24 * num + 24;
    size_arr = 16 * num + 32;
    printf("Объем занимаемой памяти очереди на основе МАССИВА : %d байт\n", size_arr);
    printf("Объем занимаемой памяти очереди на основе СПИСКА : %d байт\n\n", size_list);

    return OK;
}



int add_elems_in_arr_q(array_queue_t *queue)
{
    if (queue->cur_size == queue->capacity)
    {
        printf("Невозможно добавить элементы в очередь так как очередь заполнена\n");
        return NO_ELEMENTS;
    }

    int count, rc;
    printf("Введеите количество добавляемых элементов : ");
    rc = scanf("%d", &count);
    printf("\n");

    if (rc != 1 || count > queue->capacity - queue->cur_size || count <= 0)
    {
        printf("Неверное количество добавляемых элементов в очередь!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }

    task_t task;
    for (int i = 0; i < count; i++)
    {
        task = generate_task(1);
        push_arr_queue(queue, task);
    }

    return OK;
}



int del_elems_in_arr_q(array_queue_t *queue)
{
    if (queue->cur_size <= 0)
    {
        printf("Ошибка. Очередь пуста, невозможно удалить элементы из очереди!\n");
        return NO_ELEMENTS;
    }

    int count, rc;
    printf("Введеите количество удаляемых элементов : ");
    rc = scanf("%d", &count);
    printf("\n");

    if (rc != 1 || count > queue->cur_size || count <= 0)
    {
        printf("Неверное количество удаляемых элементов из очереди!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }

    task_t task;
    for (int i = 0; i < count; i++)
    {
        pop_arr_queue(queue, &task);
        printf("Удаленный элемент - %lf \n", task.time);
    }
    printf("\n");


    return OK;
}



int handle_array_queue()
{
    int num, choice;
    printf("\nВведите количество элементов очереди (до 1000000) : ");
    int rc = scanf("%d", &num);

    if (rc != 1 || num > 1000000 || num <= 0)
    {
        printf("Неверное количество элементов!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }
    array_queue_t arr_q;
    create_arr_queue(&arr_q, num);

    while (1)
    {
        printf("0 - выход в главное меню\n"
               "1 - добавить элементы в очередь\n"
               "2 - удалить элементы из очереди\n"
               "3 - вывести элементы очереди и их адреса в памяти на экран\n");

        printf("Выберите пункт : ");
        rc = scanf("%d", &choice);
        printf("\n");

        if (rc != 1 || choice < 0 || choice > 4)
        {
            printf(ERROR_IN_CHOICE_COMMAND_MSG);
            return ERROR_IN_CHOICE_COMMAND;
        }

        rc = OK;

        switch (choice)
        {
        case 0:
            return OK;
            break;
        
        case 1:
            add_elems_in_arr_q(&arr_q);
            break;
        case 2:
            del_elems_in_arr_q(&arr_q);
            break;
        case 3:
            print_arr_queue(&arr_q);
            break;

        default:
            break;
        }

        if (rc != OK)
            return rc;
    }

    return OK;
}



int add_elems_in_list_q(list_queue_t *queue)
{
    if (queue->cur_size == queue->capacity)
    {
        printf("Невозможно добавить элементы в очередь так как очередь заполнена\n");
        return NO_ELEMENTS;
    }

    int count, rc;
    printf("Введеите количество добавляемых элементов : ");
    rc = scanf("%d", &count);
    printf("\n");

    if (rc != 1 || count > queue->capacity - queue->cur_size || count <= 0)
    {
        printf("Неверное количество добавляемых элементов в очередь!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }

    task_t task;
    for (int i = 0; i < count; i++)
    {
        task = generate_task(1);
        push_list_queue(queue, task);
    }

    return OK;
}



int del_elems_in_list_q(list_queue_t *queue)
{
    if (queue->cur_size <= 0)
    {
        printf("Ошибка. Очередь пуста, невозможно удалить элементы из очереди!\n");
        return NO_ELEMENTS;
    }

    int count, rc;
    printf("Введеите количество удаляемых элементов : ");
    rc = scanf("%d", &count);
    printf("\n");

    if (rc != 1 || count > queue->cur_size || count <= 0)
    {
        printf("Неверное количество удаляемых элементов из очереди!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }

    task_t task;
    for (int i = 0; i < count; i++)
    {
        pop_list_queue(queue, &task);
        printf("Удаленный элемент - %lf \n", task.time);
    }
    printf("\n");


    return OK;
}


int handle_list_queue()
{
    int num, choice;
    printf("\nВведите количество элементов очереди (до 1000000) : ");
    int rc = scanf("%d", &num);

    if (rc != 1 || num > 1000000 || num <= 0)
    {
        printf("Неверное количество элементов!\n");
        return ERROR_IN_AMOUNT_ELEMS;
    }
    list_queue_t list_q;
    create_list_queue(&list_q, num);

    while (1)
    {
        printf("0 - выход в главное меню\n"
               "1 - добавить элементы в очередь\n"
               "2 - удалить элементы из очереди\n"
               "3 - вывести элементы очереди и их адреса в памяти на экран\n");

        printf("Выберите пункт : ");
        rc = scanf("%d", &choice);
        printf("\n");

        if (rc != 1 || choice < 0 || choice > 4)
        {
            printf(ERROR_IN_CHOICE_COMMAND_MSG);
            return ERROR_IN_CHOICE_COMMAND;
        }

        rc = OK;

        switch (choice)
        {
        case 0:
            return OK;
            break;
        
        case 1:
            add_elems_in_list_q(&list_q);
            break;
        case 2:
            del_elems_in_list_q(&list_q);
            break;
        case 3:
            print_list_queue(&list_q);
            break;

        default:
            break;
        }

        if (rc != OK)
            return rc;
    }

    return OK;
}