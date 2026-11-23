#include "sdk.h"

void extract_bits(uint nb, unsigned int *bits)
{
    unsigned int mask[8];

    for (int i = 0; i < 8; i++)
        mask[i] = 1 << i;
    int j = 7;
    for (int i = 0; i < 8; i++) {
        bits[i] = (nb & mask[j]) >> j;
        j--;
    }
}

unsigned int bits_to_byte(unsigned int *bits)
{
    char byte = 0;
    for (int i = 0; i < 8; i++) {
        byte = (byte << 1) | (bits[i] & 1);
    }
    return byte;
}
