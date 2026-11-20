#include "sdk.h"

int word_array_len(char **array)
{
    if (!array) return 0;
    int len = 0;
    for (int i = 0; array[i]; i++)
        len++;
    return len;
}

void free_word_array(char **array)
{
    if (!array) return;
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

void print_word_array(char **array) {
    if (!array) return;
    for (int i = 0; array[i]; i++) {
        printf("%s\n", array[i]);
    }
}