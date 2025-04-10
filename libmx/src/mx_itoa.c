#include "libmx.h"

char *mx_itoa(int number) {
    if (number == 0) {
        char *str = malloc(2);
        if (!str) return NULL; 
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    
    if (number == -2147483648) {
        char *str = malloc(12);
        if (!str) return NULL; 
        str = "-2147483648";
        return str;
    }

    int temp = number;
    int length = (number < 0) ? 1 : 0; 
    while (temp != 0) {
        temp /= 10;
        length++;
    }

    char *str = malloc(length + 1); 
    if (!str) return NULL; 

    str[length] = '\0'; 

    if (number < 0) {
        str[0] = '-';
        number = -number;
    }

    for (int i = length - 1; i >= (str[0] == '-' ? 1 : 0); i--) {
        str[i] = (number % 10) + '0';
        number /= 10;
    }

    return str;
}
