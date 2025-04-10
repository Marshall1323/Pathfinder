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

bridge *read_bridge(char *filename) {
    char *fileContent = mx_file_to_str(filename);
    fileContent = remove_first_line(fileContent); 
    int bridgeCount = mx_count_words(fileContent, '\n'); 
    struct bridge *bridgesArray = malloc(bridgeCount * sizeof(bridge));
    char **lines = mx_strsplit(fileContent, '\n');
    for (int index = 0; index < bridgeCount; index++) { 
        char **lengthAndIslands = mx_strsplit(lines[index], ','); 
        char **islandNames = mx_strsplit(lengthAndIslands[0], '-'); 

        struct bridge tempBridge = {
            islandNames[0], 
            0, 
            islandNames[1], 
            0, 
            mx_atoi(lengthAndIslands[1])
        };

        bridgesArray[index] = tempBridge; 
        for (int j = 0; j < 2; j++) {
            free(lengthAndIslands[j]); 
        }
        free(lengthAndIslands); 
        free(islandNames); 
    }

    free(fileContent); 
    for (int i = 0; i < bridgeCount + 1; i++) { 
        free(lines[i]); 
    }
    free(lines); 
    return bridgesArray; 
}
