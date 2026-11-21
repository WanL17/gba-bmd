#ifndef ROM_H
    #define ROM_H

    #define FIXED_VALUE_DEFAULT 96
    #define RESERVED_AREA_VALUE 0
    #define RESERVED_AREA_LEN 7
    #define ENTRY_POINT_LEN 4
    #define GAME_CODE_LEN 4
    #define GAME_TITLE_LEN 12
    #define NINTENDO_LOGO_LEN 156

typedef struct rom_entry_s {
    bool valid;
    char *raw;
    char *opcode;
} rom_entry_t;

typedef struct rom_marker_code_s {
    char *id;
    char *developer;
} rom_marker_code_t;

typedef struct rom_checksum_s {
    bool valid;
    char *rom;
    char *our;
} rom_checksum_t;

typedef struct rom_s {
    char *filename;
    struct stat file_infos;
    int file;
    char entry[ENTRY_POINT_LEN + 1];
    char logo[NINTENDO_LOGO_LEN + 1];
    char title[GAME_TITLE_LEN + 1];
    char game_code[GAME_CODE_LEN + 1];
    rom_marker_code_t marker_code;
    int fixed_value;
    char *dev_type;
    char reserved[RESERVED_AREA_LEN + 1];
    char *soft_ver;
    rom_checksum_t checksum;
    int cursor;
} rom_t;

int getEntryPoint(rom_t *rom);
int getNintendoLogo(rom_t *rom);
int getGameTitle(rom_t *rom);
int getGameCode(rom_t *rom);
int getFixedValue(rom_t *rom);
int getReservedArea(rom_t *rom);

void displayRomDump(rom_t *rom);
int header_dump(char *filename);

#endif