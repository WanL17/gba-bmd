#ifndef LIB_H
    #define LIB_H

    #define GREEN_COLOR "\033[32m"
    #define RED_COLOR "\033[31m"
    #define WHITE_COLOR "\033[39m"
    #define BLUE_COLOR "\033[34m"

typedef char* string;

typedef struct error_s {
    bool er;
    char *output;
} error_t;

int word_array_len(char **array);
void free_word_array(char **array);
void print_word_array(char **array);
void print_error(error_t error);
int getHexadecimalNumber(unsigned int nb);
void print_hexa(unsigned int nb, bool big);
void print_mem_adress(string adress, bool big);
void extract_bits(uint nb, unsigned int *bits);
unsigned int bits_to_byte(unsigned int *bits);
int print(string str);

#endif