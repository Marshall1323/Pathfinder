#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int word_count = 0;
    bool in_word = false;

    while (*str) {
        if (*str == c) {
            in_word = false;  
        } else {
            if (!in_word) {
                word_count++;  
                in_word = true;
            }
        }
        str++;
    }

    return word_count;
}
