#include "../headers/constants.h"
#include "../headers/info.h"
#include "../headers/iostream.h"
#include "../headers/array_queue.h"
#include "../headers/list_queue.h"
#include "../headers/common_functions.h"
#include "../headers/common_data_structures.h"
#include "../headers/handle_list_service.h"


int main()
{
    srand(time(0));

    int rc, choice = -1;

    while (1)
    {
        print_menu_info();
        
        rc = scanf("%d", &choice);

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
            handle_list_service();
            break;
        case 2:
            rc = comparison_queue();
            break;
        case 3:
            rc = handle_array_queue();
            break;
        case 4:
            rc = handle_list_queue();
            break;

        default:
            break;
        }

        if (rc != OK)
            return rc;
    }



    return OK;
}


        




        