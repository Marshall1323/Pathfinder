#include "libmx.h"

char *mx_file_to_str(const char *file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return NULL; 
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (size < 0) {
        fclose(fp);
        return NULL; 
    }

    char *content = (char *)malloc((size_t)size + 1);
    if (content == NULL) {
        fclose(fp);
        return NULL; 
    }

    size_t bytesRead = fread(content, 1, (size_t)size, fp);
    if (bytesRead != (size_t)size) {
        free(content);
        fclose(fp);
        return NULL; 
    }

    content[size] = '\0'; 
    fclose(fp);
    return content;
}
