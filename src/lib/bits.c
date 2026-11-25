#include "sdk.h"

uint extract_bit(uint nb, uint index)
{
    if (index > 7 || index < 0) return 0;
    uint mask;
    mask = 1 << index;
    return (nb & mask) >> index;
}

void extract_bits(uint nb, unsigned int *bits)
{
    uint mask[8];

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
