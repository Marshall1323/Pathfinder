#include "libmx.h"

char *mx_nbr_to_hex(unsigned long number) {
    unsigned long temp = number;
    int num_digits = (temp == 0) ? 1 : 0; 

    while (temp > 0) {
        temp /= 16;
        num_digits++;
    }

    char *hex_str = (char *)malloc(num_digits + 1);
    if (hex_str == NULL) {
        return NULL; 
    }

    hex_str[num_digits] = '\0'; 

    if (number == 0) {
        hex_str[0] = '0'; 
        return hex_str;
    }

    while (number > 0) {
        int remainder = number % 16;
        if (remainder < 10) {
            hex_str[--num_digits] = '0' + remainder;
        } else {
            hex_str[--num_digits] = 'a' + (remainder - 10);
        }
        number /= 16;
    }

    return hex_str;
}
