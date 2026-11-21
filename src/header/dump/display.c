#include "sdk.h"

static void displayRomHeaderEntryPoint(rom_t *rom)
{
    write(1, "├── entry:\n", 17);
    write(1, "│"TAB"├── code: 0x", 24);
    for (int i = 0; i < 4; i++)
        print_hexa(rom->entry[i], false);
    printf("\n");
}

static void displayRomHeaderLogo(rom_t *rom)
{
    printf("├── nintendo logo: \n");
    printf("│"TAB"├── status: \n");
    printf("│"TAB"└── debugging: \n");
}

static void displayRomHeaderGameCode(rom_t *rom)
{
    printf("├── game code:\n");
    printf("│"TAB"├── code: %s\n", rom->game_code);
    printf("│"TAB"├── date: ");
    switch (rom->game_code[0]) {
        case 'B':
            printf("2003 (new)\n");
            break;
        case 'F':
            printf("Famicom/NES (software emulated NES games)\n");
            break;
        case 'P':
            printf("e-Reader (dot-code scanner)\n");
            break;
        default:
            printf("2001..2003 (old)\n");
            break;
    }
    printf("│"TAB"└── language: ");
    switch (rom->game_code[3]) {
        case 'P':
            printf("Europe/Elsewhere\n");
            break;
        case 'J':
            printf("Japan\n");
            break;
        case 'F':
            printf("French\n");
            break;
        case 'S':
            printf("Spanish\n");
            break;
        case 'E':
            printf("USA/English\n");
            break;
        case 'D':
            printf("German\n");
            break;
        case 'I':
            printf("Italian\n");
            break;
    }
}

static void displayRomHeaderReservedArea(rom_t *rom) {
    bool valid = true;
    printf("├── reserved: ");
    for (int i = 0; i < RESERVED_AREA_LEN; i++) {
        if (getHexadecimalNumber(rom->reserved[i]) != RESERVED_AREA_VALUE) {
            valid = false;
            break;
        }
    }
    if (valid == true)
        printf("valid\n");
    else
        printf("invalid\n");
}

void displayRomDump(rom_t *rom)
{
    printf("%s:\n", rom->filename);
    displayRomHeaderEntryPoint(rom);
    displayRomHeaderLogo(rom);
    printf("├── game title: %s\n", rom->title);
    displayRomHeaderGameCode(rom);
    printf("├── fixed value: ", rom->fixed_value);
    if (rom->fixed_value == FIXED_VALUE_DEFAULT)
        printf("valid ");
    else
        printf("invalid ");
    printf("(%ih)\n", rom->fixed_value);
    displayRomHeaderReservedArea(rom);
}