#ifndef LIB_H
    #define LIB_H

typedef char* string;

int word_array_len(char **array);
void free_word_array(char **array);
void print_word_array(char **array);
void print_error(error_t error);
int getHexadecimalNumber(unsigned int nb);
const char *concat(char **array);
void print_hexa(unsigned int nb, bool big);
void print_mem_adress(string adress, bool big);
void extract_bits(uint nb, unsigned int *bits);
unsigned int bits_to_byte(unsigned int *bits);
int print(string str);

#endif