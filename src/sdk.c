#include "sdk.h"

int main(int argc, char **argv)
{
    input_t input = {{0}, {false, false}, {false}, NULL, argv, argc};
    if (parse_input(&input) != EXIT_SUCCESS) {
        printf("%s: input error: %s\n", PROJECT_NAME, input.err.output);
        return EXIT_FAILURE;
    }
    if (input.opts.help == true) {
        display_helper(&input);
    }
    free_word_array(input.filenames);
    return EXIT_SUCCESS;
}