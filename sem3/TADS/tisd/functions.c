#include "constants.h"
#include "data_structures.h"

void array_copy(int source_array[], int source_length, int target_array[])
{
  for (int i = 0; i < source_length; i++)
    target_array[i] = source_array[i];
}


void shift_right(int array[], int n)
{
  for (int i = n - 1; i > 0; i--)
  {
    array[i] = array[i - 1];
  }
}

void shift_left(int array[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    array[i] = array[i + 1];
  }
}


void round_mantissa(float_num_t *num, int new_len)
{
  if (num->mantissa_len > new_len)
  {
    if (num->field_of_mantissa[new_len] >= 5)
      num->field_of_mantissa[new_len - 1]++;
    for (int i = new_len - 1; i > 0; i--)
    {
      if (num->field_of_mantissa[i] > 9)
      {
        num->field_of_mantissa[i - 1]++;
        num->field_of_mantissa[i] %= 10;
      }
    }
    num->mantissa_len = new_len;
    if (num->field_of_mantissa[0] > 9)
    {
      (num->mantissa_len)++;
      (num->order)--;
      shift_right(num->field_of_mantissa, num->mantissa_len);
      num->field_of_mantissa[1] = 0;
      num->field_of_mantissa[0] = 1;
    }
  }
}

int count_lead_nils(int number_array[], int n)
{
  int lead_nils = 0;
  for (int i = 0; i < n; i++)
  {
    if (number_array[i] != 0)
      break;
            
    lead_nils++;
  }

  return lead_nils;
}


void eliminate_lead_nils(int array[], int *n)
{
    
  int temp_array[100];
  array_copy(array, *n, temp_array);

  int i = 0;
  while (temp_array[i] == 0)
    i++;

  int count_spaces = i;

  int j = 0;
  while (i < *n)
    array[j++] = temp_array[i++];

    
  *n = *n - count_spaces;

  if (*n < 0)
    *n = 0;
}

void eliminate_last_nils(float_num_t *num)
{
  while (num->field_of_mantissa[num->mantissa_len - 1] == 0)
  {
    (num->mantissa_len)--;
  }
}

void eliminate_last_nils_for_num(int_num_t *num)
{
  while (num->number[num->number_len - 1] == 0)
  {
    (num->number_len)--;
  }
  if (num->number_len == 0)
    num->number_len = 1;
}


void multiply(int array[], int *n, int x)
{
  int temp = 0;

  for (int i = *n - 1; i > 0; i--)
  {
    array[i] = array[i] * x + temp;
    temp = 0;

    if (array[i] >= 10)
    {
      temp = array[i] / 10;
      array[i] %= 10;
    }
  }

  array[0] = array[0] * x + temp;

  if (array[0] >= 10)
  {
    (*n)++;
    shift_right(array, *n);
    array[0] = array[1] / 10;
    array[1] %= 10;
  }
}

// Compare of arrays
int array_cmp(int *array1, int length1, int *array2, int length2)
{
  if (length1 != length2)
  {
    if (length1 > length2)
      return 1;
    return -1;
  }
  else
  {
    for (int i = 0; i < length1; i++)
    {
      if (array1[i] != array2[i])
      {
        if (array1[i] > array2[i])
          return 1;

        return -1;
      } 
    }
  }

    return 0;
}

int zero_check(int *array, int length)
{
  int zero[1] = {0};
  return array_cmp(array, length, zero, 1) == 0;
}


void subtraction(int num1[], int *n1, int num2[], int n2)
{
  int i = *n1 - 1, j = n2 - 1;
  int checker = 0;

  while (i >= 0 && j >= 0)
  {
    if (num1[i] - num2[j] < 0)
    {
      num1[i] = 10 + num1[i] - num2[j];
      num1[i - 1] -= 1;
      checker = 1;
    }
    else
    {
      checker = 0;
      num1[i] -= num2[j];
    }
    i--;
    j--;
  }

  if (i > 0 && checker == 1)
  {
    while (num1[i] == -1)
    {
      if (num1[i] == -1)
      {
        num1[i] = 9;
        num1[i - 1] -= 1;
        i--;
      }
    }
  }

  if (num1[0] == 0)
  {
    eliminate_lead_nils(num1, n1);
  }

  if (*n1 <= 0)
  {
    *n1 = 1;
  }
}



//Finding multiplier
int find_multiplier(struct auxiliary_array_t *divisible, int_num_t *divisor)
{
  int multiplier = 1;
  for (; multiplier <= 9; multiplier++)
  {
    int result_of_multiply[100];
    array_copy(divisor->number, divisor->number_len, result_of_multiply);
    int result_length = divisor->number_len;
    multiply(result_of_multiply, &result_length, multiplier);
    int cmp_res = array_cmp(result_of_multiply, result_length, divisible->field, divisible->len);

    if (cmp_res == 1)
    {
      return multiplier - 1;
    }
  }

  return multiplier - 1;
}


/*
Secondary division 
*/
void secondary_div(struct auxiliary_array_t *divisible, int_num_t *divisor, int *multiplier)
{
  int multiplier_tmp = find_multiplier(divisible, divisor);
  *multiplier = multiplier_tmp;
  int result_of_multiply[MAX_MANTISSA * 2];
  array_copy(divisor->number, divisor->number_len, result_of_multiply);
  int result_length = divisor->number_len;
  multiply(result_of_multiply, &result_length, *multiplier);
  subtraction(divisible->field, &divisible->len, result_of_multiply, result_length);
}

void choice_sign(int *first, int second)
{
    if ((*first == (int)' ' && second == (int)' ') ||
        (*first == (int)'+' && second == (int)'+') ||
        (*first == (int)'-' && second == (int)'-') ||
        (*first == (int)' ' && second == (int)'+') ||
        (*first == (int)'+' && second == (int)' '))
        {
            *first = '+';
        }
        else
        {
            *first = '-';
        }
}

void main_division(float_num_t *divisible, int_num_t *divisor)
{
  if (!zero_check(divisible->field_of_mantissa, divisible->mantissa_len))
  {

    choice_sign(&divisible->sign_of_mantissa, divisor->sign_of_num);
    
    struct auxiliary_array_t temp_divisible, result_division;
    
    for (int i = 0; i < 100; i++)
    {
        temp_divisible.field[i] = 0;
    }


    temp_divisible.len = 0;
    result_division.len = 0;

    int i = 0;

    while ((i < divisible->mantissa_len || temp_divisible.len > 0) && i < MAX_MANTISSA * 2)
    {
      if (i < divisible->mantissa_len)
      {
        temp_divisible.field[temp_divisible.len] = divisible->field_of_mantissa[i];
        temp_divisible.len++;
      }

      if (i >= divisible->mantissa_len)
      {
        temp_divisible.field[temp_divisible.len] = 0;
        temp_divisible.len++;
      }

      int cmp_res = array_cmp(temp_divisible.field, temp_divisible.len, divisor->number, divisor->number_len);

      if (cmp_res == 1 || cmp_res == 0)
      {
        eliminate_lead_nils(temp_divisible.field, &temp_divisible.len);
        int result;
        
        secondary_div(&temp_divisible, divisor, &result);

        result_division.field[result_division.len] = result;
        result_division.len++;
      }

      if (cmp_res == -1)
      {
        result_division.field[result_division.len] = 0;
        result_division.len++;
      }        
      i++;
      eliminate_lead_nils(temp_divisible.field, &temp_divisible.len);
    }

    divisible->order -= count_lead_nils(result_division.field, result_division.len);
    eliminate_lead_nils(result_division.field, &result_division.len);
    
    if (result_division.len > MAX_MANTISSA + 1)
    {
      divisible->mantissa_len = MAX_MANTISSA + 1;
    }
    else
    {
      divisible->mantissa_len = result_division.len;
    }    
    int new_result_len = divisible->mantissa_len;
    array_copy(result_division.field, new_result_len, divisible->field_of_mantissa);
    round_mantissa(divisible, MAX_MANTISSA);
    eliminate_last_nils(divisible);
  }
}

