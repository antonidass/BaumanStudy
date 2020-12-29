#include "../headers/constants.h"
#include "../headers/iostream.h"
#include "../headers/functions.h"
#include "../headers/list_ops.h"

int main()
{
    int command = input_command();
    int rc;

    if (command == ERROR_IN_INPUT_COMMAND)
        return command;

    switch (command)
    {
        case out:
            rc = handle_out_command();
            break;
        case mul:
            rc = handle_mul_command();
            break;
        case sqr:
            rc = handle_sqr_command();
            break;
        case div_:
            rc = handle_div_command();
            break;
        default:
            break;
    }

    return rc;
}