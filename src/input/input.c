#include "sdk.h"

int check_file(input_t *input, int index) {
    if (!strstr(".gba", input->argv[index])) return EXIT_FAILURE;
    struct stat infos;
    if (stat(input->argv[index], &infos) == -1) return EXIT_FAILURE;
    if (!S_ISREG(infos.st_mode)) return EXIT_FAILURE;
    input->filenames = realloc(input->filenames, sizeof(char *) * word_array_len(input->filenames + 2));
    if (!input->filenames) return EXIT_FAILURE;
    input->filenames[word_array_len(input->filenames)] = strdup(input->argv[index]);
    return EXIT_SUCCESS;
}

int check_options(input_t *input, int index, char const *option) {
    return EXIT_FAILURE;
}

int check_command_header(input_t *input, int index, char const *command) {
    if (strcmp(command, input->argv[index]) == 0) {
        if (input->cmds.header == true) {
            input->err = new_error("header command already given.");
            return EXIT_CRITIC;
        }
        input->cmds.header = true;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_command_dump(input_t *input, int index, char const *command) {
    if (strcmp(command, input->argv[index]) == 0) {
        if (input->cmds.header == true) {
            input->err = new_error("dump command already given.");
            return EXIT_CRITIC;
        }
        input->cmds.dump = true;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int parse_input(input_t *input) {
    for (int i = 1; i < input->argc; i++) {
        int ret = 0;
        ret = check_command_header(input, i, "header");
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        ret = check_command_header(input, i, "hdr");
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        if (check_options(input, i, "--help") == EXIT_SUCCESS)
            continue;
        if (check_file(input, i) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
}