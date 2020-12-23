#include "../headers/constants.h"
#include "../headers/data_structures.h"
#include "../headers/array_stack.h"
#include "../headers/info.h"
#include "../headers/list_stack.h"





int main()
{
    array_stack_t arr_stack;
    list_stack_t *head_list_stack = NULL;
    arr_of_free_areas *arr_f = malloc(sizeof(arr_of_free_areas));
    arr_f->ind = -1;
    int choice = -1, count_elems, index;
    int available_capacity_arr = 0, available_capacity_list = 0, available_capacity;
    arr_stack.elems_count = -1;
    int rc;
    int input_choice;
    long rc_1;


    while (1)
    {
        print_welcome_info();
        rc = scanf("%d", &choice);

        if (rc != 1 || choice < 0 || choice > 8)
        {
            printf(ERROR_IN_CHOICE_MSG);
            free_stack(&head_list_stack, arr_f);
            return ERROR_IN_CHOICE;
        }

        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            if (!available_capacity_arr)
            {
                rc = input_available_size(&arr_stack.capacity);

                if (rc != OK)
                    return rc;
                available_capacity_arr = 1;
            }

            available_capacity = arr_stack.capacity - arr_stack.elems_count - 1;

            if (available_capacity <= 0)
            {
                printf(STACK_OVERFLOW_MSG);
                free_stack(&head_list_stack, arr_f);
                return STACK_OVERFLOW;
            }
            
            printf("Выберите способ ввода элементов стека : \n"
                   "1  - вручную\n"
                   "2  - автоматически\n");
                
            rc = scanf("%d", &input_choice);

            if (rc != 1 || input_choice < 1 || input_choice > 2)
            {
                printf("Ошибка в выборе пункта");
                free_stack(&head_list_stack, arr_f);
                return ERROR_IN_CHOICE;
            }

            printf("Введите количество добавляемых элементов (не больше %d)    : ", available_capacity);
            rc = scanf("%d", &count_elems);

            if (rc != 1 || count_elems <= 0 || count_elems > available_capacity)
            {
                printf(ERROR_IN_ADD_ELEMS_MSG);
                free_stack(&head_list_stack, arr_f);
                return ERROR_IN_ADD_ELEMS;
            }

            if (input_choice == 1)
            {
                printf("\nВведите элементы стека. Элементы стека являются адресами памяти и должны быть записаны в шестнадцатиричной системе.\n"
                "Все элементы должны быть неотрицательными и не превышать 12 символов\n");
                rc = input_arr_stack(count_elems, &arr_stack);

                if (rc == ERROR_IN_INPUT_DATA)
                {
                    printf(ERROR_IN_INPUT_DATA_MSG);
                    free_stack(&head_list_stack, arr_f);
                    return ERROR_IN_INPUT_DATA;
                }

                if (rc == STACK_OVERFLOW)
                {
                    printf(STACK_OVERFLOW_MSG);
                    free_stack(&head_list_stack, arr_f);
                    return STACK_OVERFLOW;
                }
                printf("Элементы стека успешно введены\n");

            }

            else if (input_choice == 2)
            {
                generate(&arr_stack, count_elems);
            }


           
        }
        else if (choice == 2)
        {
            if (arr_stack.elems_count == -1)
            {
                printf(NO_ELEMENTS_FOR_DELETE_MSG);
                continue;
            }

            printf("Введите количество удаляемых элементов из стека (не больше %d): ", arr_stack.elems_count + 1);
            rc = scanf("%d", &count_elems);

            if (rc != 1 || count_elems <= 0 || count_elems > arr_stack.elems_count + 1)
            {
                printf(ERROR_IN_DELETE_ELEMS_MSG);
                free_stack(&head_list_stack, arr_f);
                return ERROR_IN_DELETE_ELEMS;
            }
            for (int i = 0; i < count_elems; i++)
            {
                rc_1 = delete_element_in_arr_stack(&arr_stack);

                if (rc_1 == EMPTY_STACK)
                {
                    printf(EMPTY_STACK_MSG);
                    free_stack(&head_list_stack, arr_f);
                    return EMPTY_STACK;
                }
                printf("Удален элемент = 0x%lx\n", rc_1);

            }
        }
        else if (choice == 3)
        {
            if (arr_stack.elems_count == -1)
            {
                printf(NO_ELEMS_FOR_PRINT_MSG);
                continue;
            }
            print_arr(&arr_stack);
        }
        else if (choice == 4)
        {
            
            if (!available_capacity_list)
            {
                rc = input_available_size(&available_capacity_list);

                index = -1;
                if (rc != OK)
                    return rc;
            }
            else if (head_list_stack == NULL)
            {
                index = -1;
            }
            else
            {
                index = head_list_stack->index;
            }
            
            available_capacity = available_capacity_list - index - 1;
            

            if (available_capacity <= 0)
            {
                printf(STACK_OVERFLOW_MSG);
                free_stack(&head_list_stack, arr_f);
                return STACK_OVERFLOW;
            }

            printf("Введите количество добавляемых элементов (не больше %d)    : ", available_capacity);
            rc = scanf("%d", &count_elems);

            if (rc != 1 || count_elems <= 0 || count_elems > available_capacity_list)
            {
                printf(ERROR_IN_ADD_ELEMS_MSG);
                free_stack(&head_list_stack, arr_f);
                return ERROR_IN_ADD_ELEMS;
            }

            rc = input_list_stack(count_elems, &head_list_stack);

            check_arr_f(head_list_stack, arr_f);

            if (rc == ERROR_IN_INPUT_DATA)
            {
                printf(ERROR_IN_INPUT_DATA_MSG);
                free_stack(&head_list_stack, arr_f);

                return ERROR_IN_INPUT_DATA;
            }
            printf("Элементы стека успешно введены\n");

        }
        else if (choice == 5)
        {
            if (head_list_stack == NULL)
            {
                printf(NO_ELEMENTS_FOR_DELETE_MSG);
                continue;
            }
            
            printf("Введите количество удаляемых элементов из стека (не больше %d): ", head_list_stack->index + 1);
            rc = scanf("%d", &count_elems);

            if (rc != 1 || count_elems <= 0 || count_elems > head_list_stack->index + 1)
            {
                printf(ERROR_IN_DELETE_ELEMS_MSG);
                free_stack(&head_list_stack, arr_f);
                return ERROR_IN_DELETE_ELEMS;
            }
            for (int i = 0; i < count_elems; i++)
            {
                printf("Удален элемент = 0x%lx \n", delete_element_in_list_stack(&head_list_stack, arr_f));
            }
        }
        else if (choice == 6)
        {
            if (head_list_stack  == NULL)
            {
                printf(NO_ELEMS_FOR_PRINT_MSG);
                continue;
            }
            print_list_stack(head_list_stack);
        }
        else if (choice == 7)
        {
            if (arr_f->ind == -1)
            {
                printf("Массив освободившихся областей пуст!\n");
                continue;
            }

            print_arr_free(arr_f);
        }
        else if (choice == 8)
        {
            rc = time_counting();

            if (rc != OK)
                return rc;
        }
    }
    

    free_stack(&head_list_stack, arr_f);
    free(arr_f);


    return OK;
}