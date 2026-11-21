#include "sdk.h"


int sdk_header(input_t *input)
{
    int ret = EXIT_SUCCESS;
    switch (input->opt) {
        case DUMP :
            if (!input->filenames) {
                input->err = new_error("no gba rom files given.");
                return EXIT_FAILURE;
            }
            for (int i = 0; input->filenames[i]; i++) {
                ret = header_dump(input->filenames[i]);
                if (ret != EXIT_SUCCESS)
                    return ret;
            }
            return EXIT_SUCCESS;
        case GEN :
            return EXIT_SUCCESS;
        default :
            break;
        return EXIT_FAILURE;
    }
}

int sdk(input_t *input)
{
    int ret = EXIT_FAILURE;
    if (input->arg == HELP) {
        display_helper(input);
        free_word_array(input->filenames);
        return EXIT_SUCCESS;
    }
    switch (input->cmd) {
        case HEADER :
            ret = sdk_header(input);
            break;
        default :
            break;
    }
    free_word_array(input->filenames);
    return EXIT_FAILURE;
}

int main(int argc, char **argv)
{
    input_t input = {{0}, NO_CMD, NO_OPT, NO_ARG, NULL, 0, argv};
    if (parse_input(&input) != EXIT_SUCCESS || input.err.er == true) {
        printf("%s: input error: %s\n", PROGRAM_NAME, input.err.output);
        return EXIT_FAILURE;
    }
    sdk(&input);
    return EXIT_SUCCESS;
}