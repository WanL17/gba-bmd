#include "sdk.h"

static void displayRomHeaderEntryPoint(rom_header_t *rom)
{
    print("├── entry:\n");
    print("│"TAB"├── valid: ");
    if ((uint8_t)rom->entry.adress[3] == B_INSTRUCTION)
        print(GREEN_COLOR"valid\n"WHITE_COLOR);
    else
        print(RED_COLOR"invalid\n"WHITE_COLOR);
    print("│"TAB"├── raw: 0x");
    for (int i = 3; i >= 0; i--)
        print_hexa(rom->entry.adress[i], false);
    printf("\n│"TAB"└── opcode: %p\n", rom->entry.opcode);
}

static void displayRomHeaderLogo(rom_header_t *rom)
{
    printf("├── nintendo logo: \n");
    printf("│"TAB"├── status: ");
    if (strcmp(rom->logo.logo_hexa, NINTENDO_LOGO_TEMPLATE) == 0)
        printf(GREEN_COLOR"valid\n"WHITE_COLOR);
    else
        printf(RED_COLOR"invalid\n"WHITE_COLOR);
    printf("│"TAB"└── debugging: ");
    if (rom->logo.debug == 1)
        printf(GREEN_COLOR"enabled\n"WHITE_COLOR);
    else
        printf(RED_COLOR"disabled\n"WHITE_COLOR);
}

static void displayRomHeaderGameCode(rom_header_t *rom)
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

static void displayRomMakerCode(rom_header_t *rom)
{
    printf("├── maker code: \n");
    printf("│"TAB"├── id: %s\n", rom->maker_code);
    printf("│"TAB"└── developer: ");
    switch (rom->maker_code[0] + rom->maker_code[1]) {
        case 97:
            printf("Nintendo");
            break;
        default:
            printf("Other");
    }
    printf("\n");
}

static void displayRomHeaderReservedArea(rom_header_t *rom) {
    bool valid = true;
    printf("├── reserved: ");
    for (int i = 0; i < RESERVED_AREA_LEN + SECOND_RESERVED_AREA_LEN; i++) {
        if (getHexadecimalNumber(rom->reserved[i]) != RESERVED_AREA_VALUE) {
            valid = false;
            break;
        }
    }
    if (valid == true)
        printf(GREEN_COLOR"valid\n"WHITE_COLOR);
    else
        printf(RED_COLOR"invalid\n"WHITE_COLOR);
}

static void displayChecksum(rom_header_t *rom) {
    printf("└── checksum:\n");
    printf(" "TAB"├── valid: ");
    if (rom->checksum[CHECKSUM_OUR_INDEX] == rom->checksum[CHECKSUM_ROM_INDEX])
        printf(GREEN_COLOR"valid\n"WHITE_COLOR);
    else
        printf(RED_COLOR"invalid\n"WHITE_COLOR);
    printf(" "TAB"├── rom: %x\n", rom->checksum[CHECKSUM_ROM_INDEX]);
    printf(" "TAB"└── our: %x\n", rom->checksum[CHECKSUM_OUR_INDEX]);
}

void displayRomHeaderDump(rom_header_t *rom)
{
    printf(WHITE_COLOR);
    printf(BLUE_COLOR"%s"WHITE_COLOR":\n", rom->filename);
    displayRomHeaderEntryPoint(rom);
    displayRomHeaderLogo(rom);
    printf("├── game title: %s\n", rom->title);
    displayRomHeaderGameCode(rom);
    displayRomMakerCode(rom);
    printf("├── fixed value: ", rom->fixed_value);
    if (rom->fixed_value == FIXED_VALUE_DEFAULT)
        printf(GREEN_COLOR"valid "WHITE_COLOR);
    else
        printf(RED_COLOR"invalid "WHITE_COLOR);
    printf("(%xh)\n", rom->fixed_value);
    printf("├── unit code: %02i\n", rom->unit_code);
    printf("├── device type: %02ih\n", rom->dev_type);
    displayRomHeaderReservedArea(rom);
    printf("├── software version: %02ih\n", rom->soft_ver);
    displayChecksum(rom);
}