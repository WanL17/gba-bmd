#ifndef LIB_H
    #define LIB_H

int word_array_len(char **array);
void free_word_array(char **array);
void print_word_array(char **array);
void print_error(error_t error);
int getHexadecimalNumber(unsigned int nb);
const char *concat(char **array);
void print_hexa(unsigned int nb, bool big);

#endif