#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = mx_strlen(str);
    
    size_t start = 0;
    size_t end = len - 1;
    
    while (start <= end && mx_isspace((unsigned char)str[start])) {
        start++;
    }
    
    while (end >= start && mx_isspace((unsigned char)str[end])) {
        end--;
    }
    
    if (start > end) {
        return mx_strdup(""); 
    }
    
    size_t trimmed_len = end - start + 1;
    
    char *trimmed_str = (char *)malloc(trimmed_len + 1);
    if (trimmed_str == NULL) {
        return NULL;
    }

    mx_strncpy(trimmed_str, str + start, trimmed_len);
    
    trimmed_str[trimmed_len] = '\0';
    
    return trimmed_str;
}
