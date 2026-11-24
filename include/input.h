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
    HELP,
    GEN_ARGS
} args_enum_t;

#define HEADER_GEN_BINARY 0
#define HEADER_GEN_OUTPUT 1
#define HEADER_GEN_NAME 2

typedef struct input_args_s {
    args_enum_t type;
    string gen_args[3];
} input_args_t;

typedef struct input_s {
    error_t err;
    cmd_enum_t cmd;
    input_args_t args;
    options_enum_t option;
    char **filenames;
    int files_index;
    char **argv;
    int index;
} input_t;

error_t new_error(char *output);
int parse_input(input_t *input);
void display_helper(input_t *input);
int input_error_handling(input_t *input);

#endif