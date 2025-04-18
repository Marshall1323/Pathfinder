#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *ptr1 = s1;
    const unsigned char *ptr2 = s2;

    while (n--) {
        if (*ptr1 != *ptr2) {
            return *ptr1 - *ptr2;
        }
        ptr1++;
        ptr2++;
    }
    return 0;
}

