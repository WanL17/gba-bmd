#include "sdk.h"

int check_file(input_t *input) {
    if (!strstr(input->argv[input->index], ".gba")) {
        input->err = new_error("invalid input given.");
        return EXIT_FAILURE;
    }
    struct stat infos;
    if (stat(input->argv[input->index], &infos) == FAIL) {
        input->err = new_error("rom file not found.");
        return EXIT_FAILURE;
    }
    if (!S_ISREG(infos.st_mode)) {
        input->err = new_error("given input is not a file.");
        return EXIT_FAILURE;
    }
    input->filenames = realloc(input->filenames, sizeof(string) * (input->files_index + 2));
    if (!input->filenames) {
        input->err = new_error("memory error while parsing input.");
        return EXIT_FAILURE;
    }
    input->filenames[input->files_index] = strdup(input->argv[input->index]);
    input->files_index++;
    input->filenames[input->files_index] = NULL;
    return EXIT_SUCCESS;
}

int check_args(input_t *input) {
    if (strcmp("--help", input->argv[input->index]) == 0) {
        if (input->args.type != NO_ARG) {
            input->err = new_error("another argument already given.");
            return EXIT_CRITIC;
        }
        input->args.type = HELP;
        return EXIT_SUCCESS;
    }
    if (strcmp("--binary", input->argv[input->index]) == 0
        || strcmp("--output", input->argv[input->index]) == 0
        || strcmp("--name", input->argv[input->index]) == 0) {
        if (!input->argv[input->index + 1] || input->args.type == HELP) {
            input->err = new_error("error in arguments");
            return EXIT_CRITIC;
        }
        input->args.type = GEN_ARGS;
    }
    if (strcmp("--binary", input->argv[input->index]) == 0) {
        if (input->args.type == GEN_ARGS && input->args.gen_args[HEADER_GEN_BINARY]) {
            input->err = new_error("binary arg already given.");
            return EXIT_CRITIC;
        }
        input->index++;
        input->args.gen_args[HEADER_GEN_BINARY] = strdup(input->argv[input->index]);
        if (!input->args.gen_args[HEADER_GEN_BINARY]) {
            input->err = new_error("memory error while parsing input.");
            return EXIT_CRITIC;
        }
        return EXIT_SUCCESS;
    }
    if (strcmp("--output", input->argv[input->index]) == 0) {
        if (input->args.type == GEN_ARGS && input->args.gen_args[HEADER_GEN_OUTPUT]) {
            input->err = new_error("output arg already given.");
            return EXIT_CRITIC;
        }
        input->index++;
        input->args.gen_args[HEADER_GEN_OUTPUT] = strdup(input->argv[input->index]);
        if (!input->args.gen_args[HEADER_GEN_OUTPUT]) {
            input->err = new_error("memory error while parsing input.");
            return EXIT_CRITIC;
        }
        return EXIT_SUCCESS;
    }
    if (strcmp("--name", input->argv[input->index]) == 0) {
        if (input->args.type == GEN_ARGS && input->args.gen_args[HEADER_GEN_NAME]) {
            input->err = new_error("name arg already given.");
            return EXIT_CRITIC;
        }
        input->index++;
        input->args.gen_args[HEADER_GEN_NAME] = strdup(input->argv[input->index]);
        if (!input->args.gen_args[HEADER_GEN_NAME]) {
            input->err = new_error("memory error while parsing input.");
            return EXIT_CRITIC;
        }
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_options(input_t *input) {
    if (strcmp("dump", input->argv[input->index]) == 0) {
        if (input->option == DUMP) {
            input->err = new_error("dump option already given.");
            return EXIT_CRITIC;
        }
        input->option = DUMP;
        return EXIT_SUCCESS;
    }
    if (strcmp("gen", input->argv[input->index]) == 0) {
        if (input->option == GEN) {
            input->err = new_error("gen option already given.");
            return EXIT_CRITIC;
        }
        input->option = GEN;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_commands(input_t *input) {
    if (strcmp("header", input->argv[input->index]) == 0) {
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
    for (; input->argv[input->index]; input->index++) {
        ret = check_commands(input);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        ret = check_options(input);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        ret = check_args(input);
        if (ret == EXIT_SUCCESS)
            continue;
        else if (ret == EXIT_CRITIC)
            return EXIT_FAILURE;
        if (check_file(input) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
    return input_error_handling(input);
}