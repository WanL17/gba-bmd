#include "sdk.h"

void removeRomStruct(rom_t *rom) {
    if (rom->filename) free(rom->filename);
    close(rom->file);
}

int header_dump(char *filename)
{
    rom_t rom = {0};
    rom.filename = strdup(filename);
    if (!rom.filename) {
        print_error(new_error("memory error while parsing file."));
        return EXIT_FAILURE;
    }
    int fd = open(rom.filename, O_RDONLY);
    if (fd == -1) {
        print_error(new_error("error while opening file."));
        return EXIT_FAILURE;
    }
    rom.file = fd;
    if (stat(rom.filename, &rom.file_infos) == -1) {
        print_error(new_error("error while opening file."));
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
    displayRomDump(&rom);
    removeRomStruct(&rom);
    return EXIT_SUCCESS;
}