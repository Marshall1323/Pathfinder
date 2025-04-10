#include "libmx.h"

void mx_print_unicode(wchar_t c)
{
    unsigned char byte1, byte2, byte3, byte4;

    if (c <= 0x7F) {
        mx_printchar((char)c);
    }
    else if (c <= 0x7FF) {
        byte1 = (c >> 6) | 0xC0;
        byte2 = (c & 0x3F) | 0x80;
        mx_printchar(byte1);
        mx_printchar(byte2);
    }
    else if (c <= 0xFFFF) {
        byte1 = (c >> 12) | 0xE0;
        byte2 = ((c >> 6) & 0x3F) | 0x80;
        byte3 = (c & 0x3F) | 0x80;
        mx_printchar(byte1);
        mx_printchar(byte2);
        mx_printchar(byte3);
    }
    else if (c <= 0x10FFFF) {
        byte1 = (c >> 18) | 0xF0;
        byte2 = ((c >> 12) & 0x3F) | 0x80;
        byte3 = ((c >> 6) & 0x3F) | 0x80;
        byte4 = (c & 0x3F) | 0x80;
        mx_printchar(byte1);
        mx_printchar(byte2);
        mx_printchar(byte3);
        mx_printchar(byte4);
    }
}
