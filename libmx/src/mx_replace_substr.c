#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) return NULL;

    size_t str_len = mx_strlen(str);
    size_t sub_len = mx_strlen(sub);
    size_t replace_len = mx_strlen(replace);

    if (sub_len == 0) return mx_strdup(str);

    size_t num_replacements = 0;
    const char *p = str;
    while ((p = mx_strstr(p, sub)) != NULL) {
        num_replacements++;
        p += sub_len;
    }

    size_t new_str_len = str_len + num_replacements * (replace_len - sub_len);
    char *new_str = malloc(new_str_len + 1);
    if (!new_str) return NULL;

    char *dst = new_str;
    p = str;
    while ((p = mx_strstr(p, sub)) != NULL) {
        size_t prefix_len = p - str;
        mx_strncpy(dst, str, prefix_len);
        dst += prefix_len;
        mx_strncpy(dst, replace, replace_len);
        dst += replace_len;
        p += sub_len;
        str = p;
    }
    mx_strcpy(dst, str);

    return new_str;
}
