#ifndef INPUT_H
    #define INPUT_H

    #define EXIT_CRITIC 84

typedef struct error_s {
    bool er;
    char *output;
} error_t;

typedef struct input_option_s {
    bool help;
} input_option_t;

typedef struct input_command_s {
    bool header;
    bool dump;
    bool gen;
} input_command_t;

typedef struct input_s {
    error_t err;
    input_command_t cmds;
    input_option_t opts;
    char **filenames;
    char **argv;
    int argc;
} input_t;

error_t new_error(char *output);
int parse_input(input_t *input);


#endif