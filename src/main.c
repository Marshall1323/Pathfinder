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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        display_usage();
    }
    if (open(argv[1], O_RDONLY) < 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(1);
    }
    
    char *fileContent = mx_file_to_str(argv[1]); 
    int islandCount = mx_atoi(&fileContent[0]); 
    fileContent = remove_first_line(fileContent); 
    int bridgeCount = mx_count_words(fileContent, '\n'); 
    
    if (!check_if_file_empty(argv[1])) exit(1);
    if (!check_is_first_line(argv[1])) exit(1);
    if (!check_is_lines(argv[1])) exit(1);
    
    struct bridge *bridges = read_bridge(argv[1]);

    if (!count_islands(bridges, argv[1])) exit(1);
    if (!duplicates(bridges, argv[1])) exit(1);
    if (!checking_island(bridges, argv[1])) exit(1);
    if (!int_max(bridges, argv[1])) exit(1);
    
    char **islands = read_islands(bridges, argv[1]);
    bridges = filling_index(bridges, islands, islandCount, bridgeCount);
    int **graph = create_graph(bridges, argv[1]); 

    for (int i = 0; i < islandCount - 1; i++) {
        dijkstra(graph, i, argv[1], bridges);
    }
    for (int i = 0; i < bridgeCount; i++) {
        free(bridges[i].island1);
        free(bridges[i].island2);
    }
    for (int i = 0; i < islandCount; i++) {
        free(islands[i]);
        free(graph[i]);
    }

    free(graph);
    free(fileContent);
    free(islands);
    free(bridges);
    
    return 0;
}
