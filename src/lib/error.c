#include "sdk.h"

error_t new_error(char *output)
{
    error_t error = {0};
    error.er = true;
    error.output = output;
    return error;
}