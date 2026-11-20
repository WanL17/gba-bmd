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

int check_options(input_t *input, int index) {
    if (strcmp("--help", input->argv[index]) == 0) {
        if (input->opts.help == true) {
            input->err = new_error("helper input already given.");
            return EXIT_CRITIC;
        }
        input->opts.help = true;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int check_commands(input_t *input, int index) {
    if (strcmp("header", input->argv[index]) == 0) {
        if (input->cmds.header == true) {
            input->err = new_error("header command already given.");
            return EXIT_CRITIC;
        }
        input->cmds.header = true;
        return EXIT_SUCCESS;
    }
    if (strcmp("dump", input->argv[index]) == 0) {
        if (input->cmds.dump == true) {
            input->err = new_error("dump command already given.");
            return EXIT_CRITIC;
        }
        input->cmds.dump = true;
        return EXIT_SUCCESS;
    }
    if (strcmp("gen", input->argv[index]) == 0) {
        if (input->cmds.gen == true) {
            input->err = new_error("gen command already given.");
            return EXIT_CRITIC;
        }
        input->cmds.gen = true;
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
        if (check_file(input, i) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
}