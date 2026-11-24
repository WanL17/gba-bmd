#include "sdk.h"

int header_gen(string *gen_args) {
    int fd = open(gen_args[HEADER_GEN_BINARY], O_RDONLY);
    if (fd < 0) {
        print_error(new_error("failed to open file"));
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 3; i++)
        printf("%s\n", gen_args[i]);
    return EXIT_SUCCESS;
}