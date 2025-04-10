#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    if (s1 == NULL) { 
        return NULL;
    }
    
    size_t len = mx_strlen(s1);
    size_t copy_len = (n < len) ? n : len;
    char *dup = (char *)malloc(copy_len + 1);
    
    if (dup == NULL) { 
        return NULL;
    }
    
    for (size_t i = 0; i < copy_len; i++) {
        dup[i] = s1[i];
    }
    
    dup[copy_len] = '\0'; 
    
    return dup;
}
