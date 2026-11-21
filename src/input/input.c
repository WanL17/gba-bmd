#include "sdk.h"

int check_file(input_t *input, int index) {
    if (!strstr(input->argv[index], ".gba")) {
        input->err = new_error("invalid input given.");
        return EXIT_FAILURE;
    }
    struct stat infos;
    if (stat(input->argv[index], &infos) == -1) {
        input->err = new_error("rom file not found.");
        return EXIT_FAILURE;
    }
    if (!S_ISREG(infos.st_mode)) {
        input->err = new_error("given input is not a file.");
        return EXIT_FAILURE;
    }
    input->filenames = realloc(input->filenames, sizeof(char *) * (input->files_index + 2));
    if (!input->filenames) {
        input->err = new_error("memory error while parsing input.");
        return EXIT_FAILURE;
    }
    input->filenames[input->files_index] = strdup(input->argv[index]);
    input->files_index++;
    input->filenames[input->files_index] = NULL;
    return EXIT_SUCCESS;
}

int check_args(input_t *input, int index) {
    if (strcmp("--help", input->argv[index]) == 0) {
        if (input->arg == HELP) {
            input->err = new_error("helper arg already given.");
            return EXIT_CRITIC;
        }
        input->arg = HELP;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_options(input_t *input, int index) {
    if (strcmp("dump", input->argv[index]) == 0) {
        if (input->opt == DUMP) {
            input->err = new_error("dump option already given.");
            return EXIT_CRITIC;
        }
        input->opt = DUMP;
        return EXIT_SUCCESS;
    }
    if (strcmp("gen", input->argv[index]) == 0) {
        if (input->opt == GEN) {
            input->err = new_error("gen option already given.");
            return EXIT_CRITIC;
        }
        input->opt = GEN;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_commands(input_t *input, int index) {
    if (strcmp("header", input->argv[index]) == 0) {
        if (input->cmd == true) {
            input->err = new_error("header command already given.");
            return EXIT_CRITIC;
        }
        input->cmd = HEADER;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int parse_input(input_t *input) {
    if (word_array_len(input->argv) == 1) {
        input->err = new_error("not enough arguments.");
        return EXIT_FAILURE;
    }
    int ret = 0;
    for (int i = 1; input->argv[i]; i++) {
        ret = check_commands(input, i);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        ret = check_options(input, i);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        ret = check_args(input, i);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        if (check_file(input, i) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
    if (input->cmd == NO_CMD && input->opt != NO_OPT)
        input->err = new_error("no command given.");
    return EXIT_SUCCESS;
}