#include "sdk.h"

int header_dump(string filename)
{
    rom_header_t rom = {0};
    rom.file_path = strdup(filename);
    char **array = str_to_array(filename, '/');
    if (!array || !rom.file_path) {
        print_error(new_error("error while getting filename."));
        return EXIT_FAILURE;
    }
    rom.filename = strdup(array[word_array_len(array) - 1]);
    free_word_array(array);
    if (!rom.filename) {
        print_error(new_error("memory error while parsing file."));
        return EXIT_FAILURE;
    }
    int fd = open(rom.file_path, O_RDONLY);
    if (fd == FAIL) {
        print_error(new_error("error while opening file."));
        return EXIT_FAILURE;
    }
    rom.file = fd;
    if (stat(rom.file_path, &rom.file_infos) == FAIL) {
        close(fd);
        print_error(new_error("error while stating file."));
        return EXIT_FAILURE;
    }
    if (!S_ISREG(rom.file_infos.st_mode)) {
        close(fd);
        print_error(new_error("given rom is not a file."));
        return EXIT_FAILURE;
    }
    if (getEntryPoint(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getNintendoLogo(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getGameTitle(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getGameCode(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getMakerCode(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getFixedValue(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getMainUnitCode(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getDeviceType(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getReservedArea(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    if (getChecksum(&rom) == EXIT_FAILURE) return EXIT_FAILURE;
    displayRomHeaderDump(&rom);
    if (rom.filename) free(rom.filename);
    if (rom.file_path) free(rom.file_path);
    close(fd);
    return EXIT_SUCCESS;
}