#include "sdk.h"

static int sdk_header(input_t *input)
{
    switch (input->option) {
        case DUMP :
            for (int i = 0; input->filenames[i]; i++) {
                if (header_dump(input->filenames[i]) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        case GEN :
            if (header_gen(input->args.gen_args) != EXIT_SUCCESS)
                return EXIT_FAILURE;
            return EXIT_SUCCESS;
        default :
            break;
    }
    return EXIT_FAILURE;
}

static int sdk_build(input_t *input) {
    printf("build\n");
    return EXIT_SUCCESS;
}

static int sdk_emulator(input_t *input) {
    printf("emulator\n");
    return EXIT_SUCCESS;
}

int sdk(input_t *input)
{
    int ret = EXIT_FAILURE;
    if (input->args.type == HELP) {
        display_helper(input);
        free_word_array(input->filenames);
        return EXIT_SUCCESS;
    }
    switch (input->cmd) {
        case HEADER :
            ret = sdk_header(input);
            break;
        case BUILD :
            ret = sdk_build(input);
            break;
        case EMU :
            ret = sdk_emulator(input);
            break;
        default :
            break;
    }
    for (int i = 0; i < 3; i++) {
        if (input->args.gen_args[i])
            free(input->args.gen_args[i]);
    }
    free_word_array(input->filenames);
    return ret;
}

int main(int argc, char **argv)
{
    input_t input = {{0}, NO_CMD, {0}, NO_OPT, NULL, 0, argv, 1};
    if (parse_input(&input) != EXIT_SUCCESS || input.err.er == true) {
        printf("%s: input error: %s\n", PROGRAM_NAME, input.err.output);
        return EXIT_FAILURE;
    }
    return sdk(&input);
}