# Game Boy Advance - Bare Metal Advancement

This is a CLI in which you can create a GBA Rom, or retrieve informations from one.

## 1. SDK

A sdk was needed to parse and retrieve informations from the file. For the moment it only retrieve some informations of the header of the rom and can display them.

### 1.1 Header dump

This command is used to check the informations about a rom header anfd check if these informations are valid. \
Here is the result used on a Pokemon Emerald ROM :

```sh

$ ./sdk header dump pkm_emerald.gba

roms/pkm_emerald.gba:
├── entry:
│   ├── valid: valid
│   ├── raw: 0xea00007f
│   └── opcode: 0x204
├── nintendo logo: 
│   ├── status: valid
│   └── debugging: disabled
├── game title: POKEMON EMER
├── game code:
│   ├── code: BPEE
│   ├── date: 2003 (new)
│   └── language: USA/English
├── maker code: 
│   ├── id: 01
│   └── developer: Nintendo
├── fixed value: valid (96h)
├── unit code: 00
├── device type: 00h
├── reserved: valid
├── software version: 00h
└── checksum:
    ├── valid: valid
    ├── rom: 72
    └── our: 72
```

### 1.2 Header generation

This command is used to generate a rom header from a binary file containing a body and an output file name .

## Documentation

- https://problemkaputt.de/gbatek.htm
- https://github.com/ioncodes/ayyboy-advance