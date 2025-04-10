#include "libmx.h"

void mx_swap_char(char *char1, char *char2) {
    char temp = *char1;
    *char1 = *char2;
    *char2 = temp;
}
