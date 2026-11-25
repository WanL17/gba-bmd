#include "sdk.h"

static int count_for_array(string str, char separator) {
    int len = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == separator)
            len++;
    }
    return len;
}

char **str_to_array(char *str, char separator) {
    if (!str || separator == 0) return NULL;
    char **array = malloc(sizeof(string) * (count_for_array(str, separator) + 2));
    if (!array) return NULL;
    char *buf = strtok(str, &separator);
    int i = 0;
    for (; buf; i++) {
        array[i] = strdup(buf);
        if (!array[i]) return NULL;
        buf = strtok(NULL, &separator);
    }
    array[i] = NULL;
    return array;
}

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