#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex_str) {
    if (hex_str == NULL) {
        return 0;
    }

    unsigned long num = 0;
    while (*hex_str) {
        char current_char = *hex_str;
        unsigned long current_value;

        if (current_char >= '0' && current_char <= '9') {
            current_value = current_char - '0';
        } else if (current_char >= 'a' && current_char <= 'f') {
            current_value = current_char - 'a' + 10;
        } else if (current_char >= 'A' && current_char <= 'F') {
            current_value = current_char - 'A' + 10;
        } else {
            return 0;
        }

        num = num * 16 + current_value;
        hex_str++;
    }

    return num;
}
