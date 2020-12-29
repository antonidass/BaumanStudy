#include "my_func.h"

int main()
{
    int first_max_number, second_max_number;

    int ans = find_maximums(stdin, &first_max_number, &second_max_number);

    if (WRONG_DATA_ERR == ans)
    {
        printf(WRONG_DATA_MSG);
        return WRONG_DATA_ERR;
    }

    printf("Answer: %d %d", first_max_number, second_max_number);

    return OK;
}