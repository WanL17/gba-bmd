#include "sdk.h"

static void write_nintendo_logo(int fd) {
    uint logo[NINTENDO_LOGO_LEN];
    int j = 0;
    for (int i = 0; i < NINTENDO_LOGO_LEN; i++) {
        char buf[2];
        buf[0] = NINTENDO_LOGO_TEMPLATE[j];
        buf[1] = NINTENDO_LOGO_TEMPLATE[j + 1];
        uint hexa = strtol(buf, NULL, BASE_16_INT);
        write(fd, &hexa, sizeof(uint8_t));
        j += 2;
    }
}

static void write_game_title(int fd, string game_title, uint *checksum) {
    int i = 0;
    for (; i < strlen(game_title); i++) {
        game_title[i] = lowercase_to_uppercase(game_title[i]);
        write(fd, &game_title[i], 1);
        (*checksum) -= game_title[i];
    }
    for (; i < GAME_TITLE_LEN; i++)
        write(fd, "\0", 1);
}

static void write_game_code(int fd, uint adress, string game_title, uint *checksum) {
    write(fd, "C", 1);
    write(fd, &game_title[0], 1);
    int mid = strlen(game_title) / 2;
    if (mid % 2 != 0)
        mid += 1;
    write(fd, &game_title[mid], 1);
    write(fd, "E", 1);
    (*checksum) -= 'C' - game_title[0] - game_title[mid] - 'E';
}

void write_data_output(int fd, string game_title) {
    int instruction = 0;
    unsigned char *bytes = (unsigned char *)&instruction;
    bytes[0] = 0x2e;
    bytes[3] = B_INSTRUCTION;
    write(fd, &instruction, sizeof(int));
    write_nintendo_logo(fd);
    uint checksum = 0;
    write_game_title(fd, game_title, &checksum);
    write_game_code(fd, bytes[0], game_title, &checksum);
    char maker[MAKER_CODE_LEN] = {54, 55};
    write(fd, maker, MAKER_CODE_LEN);
    uint fixed_value = FIXED_VALUE_DEFAULT;
    checksum -= maker[0] - maker[1] - fixed_value;
    write(fd, &fixed_value, sizeof(uint8_t));
    for (int i = 0; i < MAIN_UNIT_CODE_LEN + DEVICE_TYPE_LEN + RESERVED_AREA_LEN + SOFTWARE_VERSION_LEN; i++)
        write(fd, "\0", 1);
    write(fd, &checksum, sizeof(uint8_t));
    for (int i = 0; i < 2; i++)
        write(fd, "\0", 1);
}

int create_output(char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0) {
        print_error(new_error("failed to open/create output file."));
        return FAIL;
    }
    struct stat infos;
    if (stat(filename, &infos) == FAIL) {
        close(fd);
        print_error(new_error("failed to stat output file."));
        return FAIL;
    }
    return fd;
}
