#ifndef ROM_H
    #define ROM_H

    #define FIXED_VALUE_DEFAULT 96
    #define RESERVED_AREA_VALUE 0
    #define RESERVED_AREA_LEN 7
    #define SECOND_RESERVED_AREA_LEN 2
    #define ENTRY_POINT_LEN 4
    #define GAME_CODE_LEN 4
    #define MAKER_CODE_LEN 2
    #define GAME_TITLE_LEN 12
    #define NINTENDO_LOGO_LEN 156
    #define MAIN_UNIT_CODE_LEN 1
    #define DEVICE_TYPE_LEN 1
    #define SOFTWARE_VERSION_LEN 1
    #define CHECKSUM_LEN 1
    #define OAOH 170
    #define NINTENDO_LOGO_TEMPLATE "24FFAE51699AA2213D84820A84E409AD11248B98C0817F21A352BE199309CE2010464A4AF82731EC58C7E83382E3CEBF85F4DF94CE4B09C194568AC01372A7FC9F844D73A3CA9A615897A327FC039876231DC7610304AE56BF38840040A70EFDFF52FE036F9530F197FBC08560D68025A963BE03014E38E2F9A234FFBB3E0344780090CB88113A9465C07C6387F03CAFD625E48B380AAC7221D4F807"
    #define B_INSTRUCTION 234

typedef struct rom_header_entry_s {
    char adress[ENTRY_POINT_LEN];
    unsigned int bits[32];
    uint opcode;
} rom_header_entry_t;

typedef struct rom_header_logo_s {
    char logo_buf[NINTENDO_LOGO_LEN + 1];
    char logo_hexa[NINTENDO_LOGO_LEN * 2 + 1];
} rom_header_logo_t;

typedef struct rom_header_s {
    string filename;
    struct stat file_infos;
    unsigned int file;
    rom_header_entry_t entry;
    rom_header_logo_t logo;
    char title[GAME_TITLE_LEN + 1];
    char game_code[GAME_CODE_LEN + 1];
    char maker_code[MAKER_CODE_LEN + 1];
    unsigned int fixed_value;
    unsigned int unit_code;
    uint dev_type;
    char reserved[RESERVED_AREA_LEN + SECOND_RESERVED_AREA_LEN];
    uint soft_ver;
    uint checksum;
    int cursor;
} rom_header_t;

typedef struct rom_header_gen_s {
    string filename;
    string output;
    string name;
} rom_header_gen_t;

int getEntryPoint(rom_header_t *rom);
int getNintendoLogo(rom_header_t *rom);
int getGameTitle(rom_header_t *rom);
int getGameCode(rom_header_t *rom);
int getMakerCode(rom_header_t *rom);
int getFixedValue(rom_header_t *rom);
int getMainUnitCode(rom_header_t *rom);
int getDeviceType(rom_header_t *rom);
int getReservedArea(rom_header_t *rom);
int getSoftwareVersion(rom_header_t *rom);
int getChecksum(rom_header_t *rom);
void displayRomHeaderDump(rom_header_t *rom);

int header_dump(string filename);
int header_gen(string *gen_args);

#endif