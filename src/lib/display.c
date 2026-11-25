#include "sdk.h"

static void display_helper_header(input_t *input) {
    switch (input->option) {
        case DUMP :
            printf("Usage: %s header dump [ARGS] [GBA_FILES]...\n\n"
                TAB"dump / display cartridge header information\n\n"
                "Args:\n"
                TAB"--help"TAB"Show this message and exit.\n\n", PROGRAM_NAME);
            break;
        case GEN :
            printf("Usage: %s header gen [ARGS]\n\n"
                TAB"header generation\n\n"
                "Args:\n"
                TAB"-b"TAB"--binary FILE"TAB"input binary file [required]\n"
                TAB"-o"TAB"--output TEXT"TAB"output filename [required]\n"
                TAB"-n"TAB"--name TEXT"TAB "  internal cartridge name (default: filename)\n"
                TAB"--help"TAB TAB TAB TAB TAB"Show this message and exit.\n\n", PROGRAM_NAME);
            break;
        default :
                printf("Usage: %s header [OPTIONS]\n\n"
                    TAB"header manipulation\n\n"
                    "Options (required):\n"
                    TAB"dump"TAB"display cartridge header information\n"
                    TAB"gen"TAB" generate a rom header from a binary file\n", PROGRAM_NAME);
            break;
    }
    return;
}

void display_helper(input_t *input) {
    switch (input->cmd) {
        case HEADER :
            display_helper_header(input);
            return;
        default :
            break;
    }
    printf("Usage: %s [OPTIONS] COMMAND [ARGS]...\n\n"
        TAB"%s CLI entry\n\n"
        "Options:\n"
        TAB"--help"TAB"Show this message and exit.\n\n"
        "Commands:\n"
        TAB"header"TAB"%s header interface\n", PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME);
}

void print_mem_adress(string adress, bool big) {
    for (int i = 0; i < 4; i++) {
        print_hexa(adress[i], big);
    }
}

int print(string str) {
    return write(STDOUT_FILENO, str, strlen(str));
}