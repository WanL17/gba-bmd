#include "sdk.h"

int getEntryPoint(rom_t *rom) {
    char buf[ENTRY_POINT_LEN];
    if (read(rom->file, buf, ENTRY_POINT_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    int j = 3;
    for (int i = 0; i < 4; i++) {
        extract_bits(buf[j], &rom->entry.bits[i * 7]);
        j--;
    }
    if (rom->entry.bits[4] != 1 || rom->entry.bits[5] != 0 || rom->entry.bits[6] != 1) {
        print_error(new_error("error in entry point of rom header."));
        return EXIT_FAILURE;
    }
    unsigned char *bytes = (unsigned char *)&rom->entry.opcode;
    bytes[3] = 0x00;
    j = 2;
    for (int i = 1; i < 4; i++) {
        bytes[j] = bits_to_byte(&rom->entry.bits[i * 7]);
        j--;
    }
    rom->entry.opcode *= 4;
    rom->entry.opcode += 8;
    lseek(rom->file, 0, SEEK_SET);
    if (read(rom->file, rom->entry.adress, ENTRY_POINT_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
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
    lseek(rom->file, rom->cursor, SEEK_SET);
    if (read(rom->file, rom->game_code, GAME_CODE_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->game_code[GAME_CODE_LEN] = 0;
    rom->cursor += GAME_CODE_LEN;
    return EXIT_SUCCESS;
}

int getMakerCode(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    if (read(rom->file, rom->maker_code, MAKER_CODE_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->maker_code[MAKER_CODE_LEN] = 0;
    rom->cursor += MAKER_CODE_LEN;
    return EXIT_SUCCESS;
}

int getFixedValue(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, 1) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->fixed_value = getHexadecimalNumber(c);
    rom->cursor++;
    return EXIT_SUCCESS;
}

int getMainUnitCode(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, MAIN_UNIT_CODE_LEN) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->unit_code = getHexadecimalNumber(c);
    rom->cursor++;
    return EXIT_SUCCESS;
}

int getDeviceType(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, DEVICE_TYPE_LEN) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->dev_type = getHexadecimalNumber(c);
    rom->cursor++;
    return EXIT_SUCCESS;
}

int getReservedArea(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    if (read(rom->file, rom->reserved, RESERVED_AREA_LEN) <= 0) {
        print_error(new_error("error while reading file."));
        return EXIT_FAILURE;
    }
    rom->reserved[RESERVED_AREA_LEN] = 0;
    rom->cursor += RESERVED_AREA_LEN;
    return EXIT_SUCCESS;
}

int getSoftwareVersion(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, SOFTWARE_VERSION_LEN) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->soft_ver = getHexadecimalNumber(c);
    rom->cursor++;
    return EXIT_SUCCESS;
}

int getChecksum(rom_t *rom) {
    lseek(rom->file, rom->cursor, SEEK_SET);
    char c = 0;
    if (read(rom->file, &c, CHECKSUM_LEN) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    rom->checksum = getHexadecimalNumber(c);
    lseek(rom->file, OAOH, SEEK_SET);
    char buf[29 + 1];
    if (read(rom->file, buf, 29) <= 0) {
        print_error(new_error("error while reading file"));
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 29; i++) {
        rom->checksum -= buf[i];
    }
    return EXIT_SUCCESS;
}