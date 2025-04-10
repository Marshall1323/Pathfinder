#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    if (d == s || len == 0) {
        return dst; 
    }

    if (d < s) {
        while (len--) {
            *d++ = *s++;
        }
    } else {
        d += len;
        s += len;
        while (len--) {
            *(--d) = *(--s);
        }
    }

    return dst;
}
