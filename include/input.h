#ifndef INPUT_H
    #define INPUT_H

    #define EXIT_CRITIC 84
    #define TAB "   "

typedef enum cmd_enum_s {
    NO_CMD,
    HEADER
} cmd_enum_t;

typedef enum options_enum_s {
    NO_OPT,
    DUMP,
    GEN
} options_enum_t;

typedef enum args_enum_s {
    NO_ARG,
    HELP
} args_enum_t;

typedef struct error_s {
    bool er;
    char *output;
} error_t;

typedef struct input_s {
    error_t err;
    cmd_enum_t cmd;
    options_enum_t opt;
    args_enum_t arg;
    char **filenames;
    int files_index;
    char **argv;
} input_t;

error_t new_error(char *output);
int parse_input(input_t *input);
void display_helper(input_t *input);

#endif