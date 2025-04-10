#include "pathfinder.h"

static char *remove_first_line(char *string) {
    if (string == NULL || *string == '\0') {
        return string; 
    }
    char *newline = mx_strchr(string, '\n');
    if (newline != NULL) {
        mx_memmove(string, newline + 1, mx_strlen(newline));
    } else {
        *string = '\0';
    }
    return string;
}

void display_usage(void) {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(1);
}

bool check_if_file_empty(char *filename) {
    char *content = mx_file_to_str(filename);
    if (content == NULL) {
        mx_printerr("error: unable to read file ");
        mx_printerr(filename);
        mx_printerr("\n");
        return false; 
    }
    if (mx_strlen(content) == 0) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        free(content);
        return false;
    }

    free(content);
    return true;
}

bool check_is_first_line(char *filename) {
    char *content = mx_file_to_str(filename);
    if (content == NULL) {
        mx_printerr("error: unable to read file ");
        mx_printerr(filename);
        mx_printerr("\n");
        return false; 
    }
    char *newline = mx_strchr(content, '\n');
    if (newline != NULL) {
        *newline = '\0'; 
    }
    if (mx_strlen(content) == 0) {
        mx_printerr("error: line 1 is not valid\n");
        free(content);
        return false;
    }
    for (int i = 0; content[i] != '\0'; i++) {
        if (!mx_isdigit(content[i])) {
            mx_printerr("error: line 1 is not valid\n");
            free(content);
            return false;
        }
    }
    if (content[0] == '0' && mx_strlen(content) > 1) {
        mx_printerr("error: line 1 is not valid\n");
        free(content);
        return false;
    }
    free(content);
    return true;
}

bool check_is_lines(char *filename) {
    char *content = mx_file_to_str(filename);
    if (content == NULL) {
        mx_printerr("error: unable to read file ");
        mx_printerr(filename);
        mx_printerr("\n");
        return false; 
    }
    int line_count = mx_count_words(content, '\n');

    char **lines = mx_strsplit(content, '\n');

    for (int i = 1; i < line_count; i++) {
        int hyphen_count = 0;
        int comma_count = 0;

        if (!mx_isalpha(lines[i][0]) || !mx_isdigit(lines[i][mx_strlen(lines[i]) - 1])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            free(content);
            for (int j = 0; j < line_count; j++) {
                free(lines[j]);
            }
            free(lines);
            return false;
        }
        for (int j = 0; j < mx_strlen(lines[i]); j++) {
            if (lines[i][j] == '-') hyphen_count++;
            if (lines[i][j] == ',') comma_count++;
        }
        if (hyphen_count != 1 || comma_count != 1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            free(content);
            for (int j = 0; j < line_count; j++) {
                free(lines[j]);
            }
            free(lines);
            return false;
        }
    }

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
    free(content);
    
    return true;
}


bool checking_island(bridge *bridges, char *filename) {
    char *fileContent = mx_file_to_str(filename); 
    fileContent = remove_first_line(fileContent); 
    int totalBridges = mx_count_words(fileContent, '\n'); 
    for (int index = 0; index < totalBridges; index++) { 
        if (mx_strcmp(bridges[index].island1, bridges[index].island2) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(index + 2)); 
            mx_printerr(" is not valid\n");
            free(fileContent);
            return false;
        }
        for (int charIndex = 0; charIndex < mx_strlen(bridges[index].island1); charIndex++) { 
            if (!mx_isalpha(bridges[index].island1[charIndex])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(index + 1)); 
                mx_printerr(" is not valid\n");
                free(fileContent);
                return false;
            }
        }
        for (int charIndex = 0; charIndex < mx_strlen(bridges[index].island2); charIndex++) { 
            if (!mx_isalpha(bridges[index].island2[charIndex])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(index + 1)); 
                mx_printerr(" is not valid\n");
                free(fileContent);
                return false;
            }
        }
    }
    
    free(fileContent);
    return true; 
}

bool duplicates(bridge *bridges, char *filename) {
    char *fileContent = mx_file_to_str(filename); 
    fileContent = remove_first_line(fileContent); 
    int bridgeCount = mx_count_words(fileContent, '\n'); 
    for (int outerIndex = 0; outerIndex < bridgeCount - 1; outerIndex++) { 
        for (int innerIndex = bridgeCount - 1; innerIndex > 0; innerIndex--) { 
            if ((mx_strcmp(bridges[outerIndex].island1, bridges[innerIndex].island1) == 0) 
                && (mx_strcmp(bridges[outerIndex].island2, bridges[innerIndex].island2) == 0) 
                && (outerIndex != innerIndex)) {

                mx_printerr("error: duplicate bridges\n");
                free(fileContent);
                return false;
            }
        }
    }
    free(fileContent); 
    return true; 
}

bool int_max(bridge *bridges, char *filename) {
    char *fileContent = mx_file_to_str(filename); 
    fileContent = remove_first_line(fileContent);
    int bridgeCount = mx_count_words(fileContent, '\n'); 
    unsigned long int totalLength = 0; 
    for (int index = 0; index < bridgeCount; index++) { 
        totalLength += bridges[index].len; 
    }
    if (totalLength > INT_MAX) { 
        mx_printerr("error: sum of bridges lengths is too big\n");
        free(fileContent);
        return false;
    }
    free(fileContent); 
    return true; 
}

