#include "../headers/functions.h"

int find_count_dividers(int *num, int k)
{
    int count_dividers = 0;

    while (*num % k == 0)
    {
        count_dividers++;
        *num /= k;
    }

    return count_dividers;
}


list_num_node_t *parse_num(int num)
{
    int k = 2, count_dividers = 0;
    list_num_node_t *head = NULL;

    while (k <= num)
    {   
        LOG_DEBUG("k = %d  num = %d", k, num);
        count_dividers = find_count_dividers(&num, k);
        LOG_DEBUG("k = %d  num = %d  count_dividers = %d", k, num, count_dividers);
    
        if (count_dividers)
        {
            push_back(&head, k, count_dividers);
        }

        k++;
    }

    return head;    
}


int handle_out_command()
{
    int num;
    int rc = input_num(&num);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;


    list_num_node_t *head = parse_num(num);

    print_list(head);

    deallocate_list_num_node(&head);

    return OK;
}



void catch_up_head_first(const list_num_node_t *head_first, list_num_node_t **head_second, list_num_node_t **res)
{
    while ((*head_second) && (*head_second)->num < head_first->num)
    {
        LOG_DEBUG("head_first = %d    head_second = %d ", head_first->num, (*head_second)->num);
        
        push_back(res, (*head_second)->num, (*head_second)->pow);
        *head_second = (*head_second)->next;
    }
}


void add_remaining_elems(list_num_node_t **head, list_num_node_t *remain_node)
{
    while (remain_node)
    {
        push_back(head, remain_node->num, remain_node->pow);
        remain_node = remain_node->next;
    }
}


list_num_node_t *mult_list_numbers(list_num_node_t *head_1, list_num_node_t *head_2)
{
    list_num_node_t *result_of_mult = NULL;

    while (head_1 && head_2)
    {
        LOG_DEBUG("head1.num = %d    head2.num = %d", head_1->num, head_2->num);

        if (head_1->num < head_2->num)
        {
            catch_up_head_first(head_2, &head_1, &result_of_mult);
        }
        else if (head_2->num < head_1->num)
        {
            catch_up_head_first(head_1, &head_2, &result_of_mult);
        }
        
        if (head_1 && head_2 && head_1->num == head_2->num)
        {
            LOG_DEBUG("%d head1 + head2", head_1->pow + head_2->pow);
            push_back(&result_of_mult, head_2->num, head_2->pow + head_1->pow);

            head_1 = head_1->next;
            head_2 = head_2->next;
        }
    }

    if (head_1)
    {
        add_remaining_elems(&result_of_mult, head_1);
    }
    if (head_2)
    {
        add_remaining_elems(&result_of_mult, head_2);
    }

    return result_of_mult;
}


int handle_mul_command()
{
    int num_1, num_2;
    int rc = input_num(&num_1);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;

    rc = input_num(&num_2);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;


    list_num_node_t *head_1 = parse_num(num_1);
    list_num_node_t *head_2 = parse_num(num_2);

    list_num_node_t *result_of_mult = mult_list_numbers(head_1, head_2);
    
    print_list(result_of_mult);

    deallocate_list_num_node(&head_1);
    deallocate_list_num_node(&head_2);
    deallocate_list_num_node(&result_of_mult);

    return OK;
}



list_num_node_t *sqr_list_num(list_num_node_t *head)
{
    list_num_node_t *result_of_sqr = NULL;

    while (head)
    {
        push_back(&result_of_sqr, head->num, head->pow * 2);
        head = head->next;
    }

    return result_of_sqr;
}


int handle_sqr_command()
{
    int num;
    int rc = input_num(&num);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;

    list_num_node_t *head = parse_num(num);

    list_num_node_t *result_of_sqr = sqr_list_num(head);

    print_list(result_of_sqr);

    deallocate_list_num_node(&result_of_sqr);
    deallocate_list_num_node(&head);
    
    return OK;
}



int power(int base, int pow)
{
    int result = 1;

    while (pow--)
        result *= base;
    
    return result;
}

int get_num_from_list_num(list_num_node_t *head)
{
    int num = 1;

    while (head)
    {
        LOG_DEBUG("power  =  %d", power(head->num, head->pow));

        num *= power(head->num, head->pow);
        head = head->next;
    }

    return num;
}


int handle_div_command()
{
    int num_1, num_2;
    int rc = input_num(&num_1);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;

    rc = input_num(&num_2);

    if (rc == ERROR_IN_INPUT_NUM)
        return rc;


    list_num_node_t *head_1 = parse_num(num_1);
    list_num_node_t *head_2 = parse_num(num_2);

    num_1 = get_num_from_list_num(head_1);
    num_2 = get_num_from_list_num(head_2);

    LOG_DEBUG("num_1 = %d   num_2 = %d", num_1, num_2);

    int result_of_div = num_1 / num_2;

    if (result_of_div == 0)
    {
        deallocate_list_num_node(&head_1);
        deallocate_list_num_node(&head_2);
        return ERROR_IN_DIV;
    }

    list_num_node_t *result_head = parse_num(result_of_div);

    print_list(result_head);

    deallocate_list_num_node(&result_head);
    deallocate_list_num_node(&head_1);
    deallocate_list_num_node(&head_2);


    return OK;
}