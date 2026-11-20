#include "sdk.h"

int main(int argc, char **argv)
{
    input_t input = {{0}, NO_CMD, NO_OPT, NO_ARG, NULL, argv, argc};
    if (parse_input(&input) != EXIT_SUCCESS || input.err.er == true) {
        printf("%s: input error: %s\n", PROJECT_NAME, input.err.output);
        return EXIT_FAILURE;
    }
    if (input.arg == HELP) display_helper(&input);
    free_word_array(input.filenames);
    return EXIT_SUCCESS;
}