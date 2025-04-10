#pragma once
#include "libmx.h"

typedef struct bridge {
    char *island1;
    int src;
    char *island2;
    int dest;
    int len;
} bridge;

//count_islands.c
bool count_islands(bridge *bridges, char *filename);

//errors.c
void display_usage();
bool check_if_file_empty(char *filename);
bool check_is_first_line(char *filename);
bool check_is_lines(char *filename);
bool checking_island(bridge *bridges, char *filename);
bool duplicates(bridge *bridges, char *filename);
bool int_max(bridge *bridges, char *filename);

//filling_indexes.c
bridge *filling_index(struct bridge *bridges, char **islandNames, int vertexCount, int edgeCount);

//read_bridge.c
bridge *read_bridge(char *filename);

//read_island.c
char **read_islands(bridge *bridges, char *filename);

//pathfinder.c
void create_matrix(int **Adj, int **arr, int N, int M, struct bridge *bridges);
int **create_graph(bridge *bridges, char *filename);
void delete_list(t_list **list);
void dijkstra(int **graph, int src, char *filename, struct bridge *bridges);

//print.c
void delete_linked(t_list **list);
bool compare_islands(void *a, void *b);
void get_path_indices(t_list **paths, t_list **parent, char **islands, int *buffer, int current_index, const int current, int source);
void *get_index_island(char **islands, int i, int size);
void show_distance(int **graph, int *index, int dist);
void show_route(char **islands, int *path, int total_size);
void show_path(char **islands, int *path, int dest, int size);
void print(int *distance, int startnode, int n, int **matrix, char **islands, t_list **pred_lists);
