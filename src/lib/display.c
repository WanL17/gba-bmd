#include "sdk.h"

static void display_helper_cmd(input_t *input) {
    switch (input->opt) {
        case GEN :
            printf("Usage: cartridge hdr dump [OPTIONS] [GBA_FILES]...\n\n"
                TAB"header generation\n\n"
                "Options:\n"
                TAB"--help"TAB"Show this message and exit.\n\n");
        case DUMP :
            printf("Usage: cartridge hdr dump [OPTIONS] [GBA_FILES]...\n\n"
                TAB"dump / display cartridge header information\n\n"
                "Options:\n"
                TAB"-b"TAB"--binary FILE"TAB"input binary file [required]\n");
        default :
            break;
    }
    return;
}

void display_helper(input_t *input) {
    switch (input->cmd) {
        case HEADER :
            display_helper_cmd(input);
            return;
        default :
            break;
    }
    printf("Usage: cartridge [OPTIONS] COMMAND [ARGS]...\n\n"
        TAB"Cartridge SDK CLI entry\n\n"
        "Options:\n"
        TAB"--help"TAB"Show this message and exit.\n\n"
        "Commands:\n"
        TAB"header"TAB"Cartridge header interface\n");
}