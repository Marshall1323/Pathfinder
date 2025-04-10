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

char **read_islands(bridge *bridges, char *filename) {
    char *fileContent = mx_file_to_str(filename); 
    int totalIslands = mx_atoi(&fileContent[0]); 
    int currentIndex = 0; 
    fileContent = remove_first_line(fileContent); 
    int bridgeCount = mx_count_words(fileContent, '\n'); 
    char **islandList = malloc(totalIslands * sizeof(char *));
    for (int i = 0; i < totalIslands; i++) {
        islandList[i] = malloc(128 * sizeof(char));
    }
    for (int i = 0; i < bridgeCount; i++) { 
        bool found = false; 

        for (int a = 0; a < currentIndex; a++) { 
            if (mx_strcmp(islandList[a], bridges[i].island1) == 0) {
                found = true; 
                break;
            }
        }
        if (!found) { 
            mx_strcpy(islandList[currentIndex], bridges[i].island1);
            currentIndex++; 
        }
        if (currentIndex > totalIslands) { 
            mx_printerr("error: invalid number of islands\n");
        }

        found = false; 

        for (int a = 0; a < currentIndex; a++) { 
            if (mx_strcmp(islandList[a], bridges[i].island2) == 0) {
                found = true; 
                break;
            }
        }
        if (!found) { 
            mx_strcpy(islandList[currentIndex], bridges[i].island2);
            currentIndex++; 
        }
        if (currentIndex > totalIslands) { 
            mx_printerr("error: invalid number of islands\n");
        }
    }
    if (currentIndex == totalIslands - 1) { 
        mx_printerr("error: invalid number of islands\n");
    }
    free(fileContent); 
    return islandList; 
}
