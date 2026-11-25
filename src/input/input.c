#include "sdk.h"

typedef struct arg_input {
    string name[2];
    args_enum_t type;
    uint hdr;
} arg_input;

typedef struct cmd_input {
    string name;
    cmd_enum_t type;
} cmd_input;

typedef struct opt_input {
    string name;
    options_enum_t type;
} opt_input;

int check_file(input_t *input) {
    if (!strstr(input->argv[input->index], ".gba")) {
        if (input->err.er == false)
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
    struct arg_input args[3] = {
        {{"--binary", "-b"}, GEN_ARGS, HEADER_GEN_BINARY},
        {{"--output", "-o"}, GEN_ARGS, HEADER_GEN_OUTPUT},
        {{"--name", "-n"}, GEN_ARGS, HEADER_GEN_NAME}
    };
    if (input->option != GEN) return EXIT_FAILURE;
    for (int i = 0; i < 3; i++) {
        if ((strcmp(args[i].name[0], input->argv[input->index]) == 0)
            || (strcmp(args[i].name[1], input->argv[input->index]) == 0)) {
            if (!input->argv[input->index + 1]) {
                input->err = new_error("invalid input for arg.");
                return EXIT_CRITIC;
            }
            if (input->args.type == GEN_ARGS && input->args.gen_args[args[i].hdr]) {
                input->err = new_error("arg already given.");
                return EXIT_CRITIC;
            }
            input->index++;
            input->args.type = GEN_ARGS;
            input->args.gen_args[args[i].hdr] = strdup(input->argv[input->index]);
            if (!input->args.gen_args[args[i].hdr]) {
                input->err = new_error("memory error while parsing input.");
                return EXIT_CRITIC;
            }
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int check_options(input_t *input) {
    switch (input->cmd) {
        case HEADER:
            break;
        default:
            return EXIT_FAILURE;
    }
    struct opt_input opts[2] = {{"dump", DUMP}, {"gen", GEN}};
    for (int i = 0; i < 2; i++) {
        if (strcmp(opts[i].name, input->argv[input->index]) == 0) {
            if (input->option != NO_OPT) {
                input->err = new_error("another option already given.");
                return EXIT_CRITIC;
            }
            input->option = opts[i].type;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int check_commands(input_t *input) {
    struct cmd_input cmds[3] = {
        {"header", HEADER},
        {"build", BUILD},
        {"emu", EMU}
    };
    for (int i = 0; i < 3; i++) {
        if (strcmp(cmds[i].name, input->argv[input->index]) == 0) {
            if (input->cmd != NO_CMD) {
                input->err = new_error("another command already given.");
                return EXIT_CRITIC;
            }
            input->cmd = cmds[i].type;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

// Parse the user input to retrieve the commands/options and arguments given and verify if there are errors.
// Return 1 if error.
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