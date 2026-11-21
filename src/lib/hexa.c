#include "sdk.h"

int getHexadecimalNumber(unsigned int nb)
{
    if (nb == 0) return 0;
    char hexa[3] = "00";
    int reste = 0;
    char hexa_chars[] = "0123456789ABCDEF";
    for (int i = 1; nb > 0 && i >= 0; i--) {
        reste = nb % 16;
        nb /= 16;
        hexa[i] = hexa_chars[reste];
    }
    hexa[2] = 0;
    return atoi(hexa);
}

void print_hexa(unsigned int nb, bool big)
{
    if (nb == 0) {
        write(1, "00", 2);
        return;
    }
    char hexa[3] = "00";
    int reste = 0;
    char hexa_chars[17];
    if (big == true)
        strcpy(hexa_chars, "0123456789ABCDEF");
    else
        strcpy(hexa_chars, "0123456789abcdef");
    for (int i = 1; nb > 0 && i >= 0; i--) {
        reste = nb % 16;
        nb /= 16;
        hexa[i] = hexa_chars[reste];
    }
    hexa[2] = 0;
    write(1, hexa, 2);
}