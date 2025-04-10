#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    char *dst_start = dst; 
    
    while (*src) {         
        *dst = *src;
        dst++;
        src++;
    }
    
    *dst = '\0';          

    return dst_start;    
}
