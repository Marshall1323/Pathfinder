#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *ptr = (unsigned char *)s + n - 1; 
    unsigned char uc = (unsigned char)c; 

    while (n > 0) {
        if (*ptr == uc) {
            return ptr; 
        }
        ptr--;
        n--;
    }
    
    return NULL; 
}
