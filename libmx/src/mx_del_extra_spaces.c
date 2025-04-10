#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) return NULL;

    int start = 0;
    int end = mx_strlen(str) - 1;
    
    while (isspace((unsigned char)str[start])) start++;
    while (end > start && isspace((unsigned char)str[end])) end--;
    
    if (start > end) return mx_strdup("");  

    int new_len = end - start + 2;  
    char *new_str = (char *)malloc(new_len);
    if (new_str == NULL) return NULL; 

    int j = 0;
    for (int i = start; i <= end; i++) {
        if (isspace((unsigned char)str[i])) {
            if (i > start && !isspace((unsigned char)str[i - 1])) {
                new_str[j++] = ' ';
            }
        } else {
            new_str[j++] = str[i];
        }
    }

    if (j > 0 && new_str[j - 1] == ' ') {
        j--;
    }
    
    new_str[j] = '\0';
    return new_str;
}
