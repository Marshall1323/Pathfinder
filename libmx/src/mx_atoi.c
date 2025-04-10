#include "libmx.h"

int mx_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    
    // Skip whitespace
    while (*str == ' ' || (*str >= 9 && *str <= 13)) {
        str++;
    }
    
    // Handle sign
    if (*str == '-' || *str == '+') {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }

    // Convert the string to an integer
    while (*str >= '0' && *str <= '9') {
        // Check for overflow
        if (result > (INT_MAX - (*str - '0')) / 10) {
            return (sign == 1) ? INT_MAX : INT_MIN; // Overflow
        }
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}
