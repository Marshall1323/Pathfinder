#include "libmx.h"

char *mx_strcat(char *restrict destination, const char *restrict source)
{
    int dest_len = mx_strlen(destination);
    int src_len = mx_strlen(source);
    int i = 0;

    while (destination[dest_len] != '\0')
    {
        dest_len++;
    }

    while (i < src_len)
    {
        destination[dest_len] = source[i];
        dest_len++;
        i++;
    }

    destination[dest_len] = '\0';

    return destination;
}
