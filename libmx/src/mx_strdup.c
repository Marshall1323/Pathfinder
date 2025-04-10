#include "libmx.h"

char *mx_strdup(const char *s1) {
    if (!s1) {
        return NULL;
    }

    int len = mx_strlen(s1);
    char *dup_str = mx_strnew(len);

    if (dup_str) {
        for (int i = 0; i < len; i++) {
            dup_str[i] = s1[i];
        }
        dup_str[len] = '\0'; 
    }

    return dup_str;
}
