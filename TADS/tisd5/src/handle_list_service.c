#include "../headers/handle_list_service.h"




task_t generate_task(int type_service)
{
    task_t task;
    
    task.type_service = type_service;

    if (type_service == 1)
        task.time = rand() % (FIRST_SERVICE_OUT * 1000000) / (double) 1000000;
    else if (type_service == 2)
        task.time = rand() % ((SECOND_SERVICE_OUT - 1) * 1000000) / (double) 1000000 + 1;

    return task;
}

int get_probability()
{
    return rand() % 100;
}


void fill_list_queue(list_queue_t *head)
{
    task_t task;
    for (int i = 0; i < TASKS_AMOUNT; i++)
    {
        task = generate_task(1);
        push_list_queue(head, task);
    }
}


void push_deleted_elem(list_queue_t *first_queue, list_queue_t *second_queue)
{
    int probability = get_probability();
    task_t task;

    // printf("Probability = %d\n", probability);
    if (probability <= 100 - PROBABILITY)
    {
        task = generate_task(2);
        push_list_queue(second_queue, task);
    }
    else if (probability > 100 - PROBABILITY)
    {
        task = generate_task(1);
        push_list_queue(first_queue, task);
    }
}


void check_tasks(int completed_tasks, const list_queue_t *first, const list_queue_t *second, int average_len_first, int average_len_second, int colls_first)
{
    int probability = get_probability();
    int first_add = 0, second_add = 0;

    if (probability < 30)
        second_add = 1;
    else
        first_add = 1;
    

    if (completed_tasks % 100 == 0)
    {
         printf(
                           "\nОбработано %d заявок.\n"
                           "Длина очереди 1 : %d\n"
                           "Длина очереди 2 : %d\n"
                           "Средняя длина очереди 1: %d\n"
                           "Средняя длина очереди 2: %d\n\n",
                            completed_tasks, first->cur_size + first_add, second->cur_size + second_add,
                            average_len_first / colls_first, average_len_second / completed_tasks);
    }
}


void push_task_in_first_queue(list_queue_t *queue)
{
    task_t task = generate_task(1);
    push_list_queue(queue, task);
}


/* 
calls_first - количество срабатываний ОА1
delta_time - разница времен обслуживания OA1 и OA2
sec_queue_elem_time - время обслуживания элемента взятого из головы во второй очереди
*/
void handle_list_service()
{
    list_queue_t first_queue, second_queue;
    create_list_queue(&first_queue, TASKS_AMOUNT);
    create_list_queue(&second_queue, TASKS_AMOUNT);
    fill_list_queue(&first_queue);

    
    int completed_tasks = 0, type_service = 1;
    int probability;
    double first_service_time = 0, sec_queue_head_elem_time = 0;
    double service_first_time = 0, service_second_time = 0, hold_time = 0;
    double delta_time;
    int average_len_first = 0, average_len_second = 0;
    int average_task_time_in_queue = 0;
    int calls_first = 0;

    
    task_t task, first_queue_task, second_queue_task;

    while (completed_tasks < 1000)
    {
        average_len_first += first_queue.cur_size;

        if (pop_list_queue(&first_queue, &first_queue_task) == EMPTY_QUEUE)
        {
            return;
        }
        calls_first++;
        first_service_time += first_queue_task.time;
        delta_time = first_queue_task.time;


        if (isEmpty_list_queue(&second_queue))
        {
            hold_time += first_queue_task.time;
            push_deleted_elem(&first_queue, &second_queue);
            continue;
        }

        sec_queue_head_elem_time = second_queue.head->task.time;

        if (delta_time >= sec_queue_head_elem_time)
        {
            while (delta_time > 0)
            {
                if (delta_time >= sec_queue_head_elem_time)
                {
                    delta_time -= sec_queue_head_elem_time;
                    average_len_second += second_queue.cur_size;
                    service_second_time += second_queue.head->task.time;
                    pop_list_queue(&second_queue, &second_queue_task);
                    
                    completed_tasks++;

                    push_task_in_first_queue(&first_queue);
                    check_tasks(completed_tasks, &first_queue, &second_queue, average_len_first, average_len_second, calls_first);
                     

                    if (isEmpty_list_queue(&second_queue))
                    {
                        hold_time += delta_time;
                        push_deleted_elem(&first_queue, &second_queue);
                        break;
                    }
                    
                    sec_queue_head_elem_time = second_queue.head->task.time;
                }
                else
                {
                    service_second_time += delta_time;
                    second_queue.head->task.time -= delta_time;
                    push_deleted_elem(&first_queue, &second_queue);
                    break;
                }
            }
        }
        else if (delta_time < sec_queue_head_elem_time)
        {
            service_second_time += delta_time;
            second_queue.head->task.time -= delta_time;
            push_deleted_elem(&first_queue, &second_queue);
        }


    }


    printf(
           "Рабочее время автомата 1: %lf (ожидаемое рабочее время: %lf, погрешность: %lf%%)\n"
           "Рабочее время автомата 2: %lf (ожидаемое рабочее время: %lf, погрешность: %lf%%)\n"
           "Количество срабатываний автомата 1: %d (ожидаемое число срабатываний автомата: 3333)\n"
           "Время простоя автомата: %lf\n"
           "Теоретичкское время простоя автомата: %lf)\n",
           first_service_time, 10000.0, fabs(first_service_time - 10000.0) / 100,
           service_second_time, 4500.0,  fabs(service_second_time - 4500) / 45,
           calls_first,
           hold_time, 10000.0 - 4500);
}