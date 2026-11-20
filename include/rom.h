#ifndef ROM_H
    #define ROM_H

typedef struct rom_entry_s {
    bool valid;
    char *raw;
    char *opcode;
} rom_entry_t;

typedef struct rom_logo_s {
    bool status;
    bool debugging;
} rom_logo_t;

typedef struct rom_game_code_s {
    char *code;
    char *date;
    char *lang;
} rom_game_code_t;

typedef struct rom_marker_code_s {
    char *id;
    char *developer;
} rom_marker_code_t;

typedef struct rom_s {
    char *filename;
    rom_entry_t entry;
    rom_logo_t logo;
    char *title;
    rom_game_code_t game_code;
    rom_marker_code_t marker_code;
    char *fixed_value;
} rom_t;

#endif