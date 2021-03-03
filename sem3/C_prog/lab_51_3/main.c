/* Сортировка пузырьком по возрастанию */

#include <stdio.h>
#include "my_functions.h"
#include <string.h>


int main(int argc, char *argv[])
{
    int ans = INITIAL_VALUE;

    if (argc < 3 || argc > 4)
    {
        printf(LAUNCH_PARAMS_MSG);
        return LAUNCH_PARAMETERS_ERR;
    }
    

    if (!strcmp(argv[1], "c"))
        ans = create_bin_file(argv[2], argv[3]);
    
    if (!strcmp(argv[1], "p"))
        ans = print_bin_file(argv[2]);

    if (!strcmp(argv[1], "s"))
        ans = sort_bin_file(argv[2]);


    if (INITIAL_VALUE == ans)
    {
        printf(ARGS_MSG);
        return INITIAL_VALUE;
    }

    if (WRITE_DATA_ERR == ans)
    {
        printf(INPUT_DATA_MSG);
        return WRITE_DATA_ERR;
    }

    if (SIZE_ERR == ans)
    {
        printf(SIZE_MSG);
        return SIZE_ERR;
    }

    if (FILE_NAME_ERR == ans)
    {
        printf(FILE_NAME_MSG);
        return FILE_NAME_ERR;
    }

    if (READ_FILE_ERR == ans)
    {
        printf(READ_FILE_MSG);
        return READ_FILE_ERR;
    }

    return ans;
}


