#include "sdk.h"

int header_gen(string *gen_args) {
    rom_header_gen_t rom = {0};
    int binary_fd = open(gen_args[HEADER_GEN_BINARY], O_RDONLY);
    if (binary_fd < 0) {
        print_error(new_error("failed to open file."));
        return EXIT_FAILURE;
    }
    struct stat infos = {0};
    if (stat(gen_args[HEADER_GEN_BINARY], &infos) == FAIL) {
        close(binary_fd);
        print_error(new_error("failed to stat file."));
        return EXIT_FAILURE;
    }
    if (infos.st_size == 0) {
        close(binary_fd);
        print_error(new_error("binary file is empty."));
        return EXIT_FAILURE;
    }
    char binary_content[infos.st_size];
    if (read(binary_fd, binary_content, infos.st_size) <= 0) {
        close(binary_fd);
        print_error(new_error("failed to read binary file."));
        return EXIT_FAILURE;
    }
    rom.args = gen_args;
    int output_fd = create_output(gen_args[HEADER_GEN_OUTPUT]);
    if (output_fd == FAIL) {
        close(binary_fd);
        print_error(new_error("binary file is empty."));
        return EXIT_FAILURE;
    }
    write_data_output(output_fd, gen_args[HEADER_GEN_NAME]);
    write(output_fd, binary_content, infos.st_size);
    close(output_fd);
    close(binary_fd);
    return EXIT_SUCCESS;
}