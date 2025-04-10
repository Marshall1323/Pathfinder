#include "libmx.h"

char *mx_strchr(const char *str, char c) {
    while (*str) {  
        if (*str == c) {
            return (char *)str;  
        }
        str++;
    }
    return NULL;  
}
