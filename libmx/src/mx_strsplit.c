#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (s == NULL) {
        return NULL;
    }
    
    int word_count = mx_count_words(s, c);
    char **result = (char **)malloc((word_count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;  
    }
    
    int index = 0, start = 0;
    for (int j = 0; j <= mx_strlen(s); j++) {
        if (s[j] == c || s[j] == '\0') {
            if (j > start) {  
                result[index] = mx_strnew(j - start);
                if (result[index] == NULL) {
                    for (int k = 0; k < index; k++) {
                        free(result[k]);
                    }
                    free(result);
                    return NULL;
                }
                mx_strncpy(result[index], s + start, j - start);
                index++;
            }
            start = j + 1;  
        }
    }
    result[word_count] = NULL;  

    return result;
}
