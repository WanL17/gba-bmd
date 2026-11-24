#include "sdk.h"

error_t new_error(char *output)
{
    error_t error = {0};
    error.er = true;
    error.output = output;
    return error;
}

void print_error(error_t error) {
    printf("%s "RED_COLOR"error"WHITE_COLOR": %s\n", PROGRAM_NAME, error.output);
}