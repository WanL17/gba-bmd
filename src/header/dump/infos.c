#include "sdk.h"

int getEntryPoint(rom_t *rom) {
    if (read(rom->file, rom->entry, ENTRY_POINT_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->entry[ENTRY_POINT_LEN] = 0;
    int nb = 0;
    unsigned char *bytes = (unsigned char *)&nb;
    bytes[0] = rom->entry[3];
    bytes[1] = rom->entry[2];
    bytes[2] = rom->entry[1];
    bytes[3] = rom->entry[0];
    rom->cursor += ENTRY_POINT_LEN;
    return EXIT_SUCCESS;
}

int getNintendoLogo(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    if (read(rom->file, rom->logo, NINTENDO_LOGO_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->logo[NINTENDO_LOGO_LEN] = 0;
    rom->cursor += NINTENDO_LOGO_LEN;
    return EXIT_SUCCESS;
}

int getGameTitle(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    if (read(rom->file, rom->title, GAME_TITLE_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->title[GAME_TITLE_LEN] = 0;
    rom->cursor += GAME_TITLE_LEN;
    return EXIT_SUCCESS;
}

int getGameCode(rom_t *rom) {
    lseek(rom->file, 172, SEEK_SET);
    if (read(rom->file, rom->game_code, GAME_CODE_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->game_code[GAME_CODE_LEN] = 0;
    rom->cursor += GAME_CODE_LEN;
    return EXIT_SUCCESS;
}

int getFixedValue(rom_t *rom) {
    lseek(rom->file, 178, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, 1) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->fixed_value = getHexadecimalNumber(c);
    rom->cursor++;
    return EXIT_SUCCESS;
}

int getReservedArea(rom_t *rom) {
    lseek(rom->file, 181, SEEK_SET);
    if (read(rom->file, rom->reserved, RESERVED_AREA_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->reserved[RESERVED_AREA_LEN] = 0;
    rom->cursor += RESERVED_AREA_LEN;
    return EXIT_SUCCESS;
}