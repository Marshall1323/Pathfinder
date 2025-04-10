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

bool count_islands(bridge *bridges, char *filename) {
    char *data = mx_file_to_str(filename);
    if (data == NULL) {
        return false;
    }

    int expected_count = mx_atoi(data);
    data = remove_first_line(data);

    int actual_count = mx_count_words(data, '\n');
    int total_size = actual_count * 2;

    char **island_a = (char **)malloc(actual_count * sizeof(char *));
    char **island_b = (char **)malloc(actual_count * sizeof(char *));
    char **all_islands = (char **)malloc(total_size * sizeof(char *));

    for (int i = 0; i < actual_count; i++) {
        island_a[i] = (char *)malloc(128 * sizeof(char));
        island_b[i] = (char *)malloc(128 * sizeof(char));
    }

    for (int i = 0; i < total_size; i++) {
        all_islands[i] = (char *)malloc(128 * sizeof(char));
    }

    for (int i = 0; i < actual_count; i++) {
        mx_strcpy(island_a[i], bridges[i].island1);
        mx_strcpy(island_b[i], bridges[i].island2);
    }

    for (int i = 0; i < actual_count; i++) {
        mx_strcpy(all_islands[i], island_a[i]);
    }

    for (int j = 0; j < actual_count; j++) {
        mx_strcpy(all_islands[actual_count + j], island_b[j]);
    }

    for (int i = 0; i < total_size; i++) {
        for (int j = i + 1; j < total_size; ) {
            if (mx_strcmp(all_islands[i], all_islands[j]) == 0) {
                mx_strncpy(all_islands[j], all_islands[total_size - 1], sizeof(all_islands[0]));
                total_size--;
            } else {
                j++;
            }
        }
    }

    free(data);
    for (int i = 0; i < actual_count; i++) {
        free(island_a[i]);
        free(island_b[i]);
    }
    free(island_a);
    free(island_b);
    for (int i = 0; i < actual_count * 2; i++) {
        free(all_islands[i]);
    }
    free(all_islands);

    if (expected_count != total_size) {
        mx_printerr("error: invalid number of islands\n");
        return false;
    }
    return true;
}
