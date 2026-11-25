#include "sdk.h"

int input_error_handling(input_t *input)
{
    if (input->cmd == NO_CMD && input->option != NO_OPT) {
        input->err = new_error("no command given.");
        return EXIT_FAILURE;
    }
    if (input->cmd == HEADER) {
        if (input->option == DUMP && !input->filenames && input->args.type != HELP) {
            input->err = new_error("no gba rom files given.");
            return EXIT_FAILURE;
        }
        if (input->option == GEN && input->args.type != HELP && (!input->args.gen_args[HEADER_GEN_BINARY] || !input->args.gen_args[HEADER_GEN_OUTPUT])) {
            input->err = new_error("missing output or binary.");
            return EXIT_FAILURE;
        }
        if (input->option == GEN && !input->args.gen_args[HEADER_GEN_NAME])
            input->args.gen_args[HEADER_GEN_NAME] = strdup("filename");
    }
    return EXIT_SUCCESS;
}
