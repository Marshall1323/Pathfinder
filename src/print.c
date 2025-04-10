#include "pathfinder.h"

void delete_linked(t_list **list) {
    t_list *current_node = *list;
    
    while (current_node) {
        t_list *next_node = current_node->next;
        
        free(current_node->data);
        free(current_node);
        
        current_node = next_node; 
    }

    *list = NULL; 
}

bool compare_islands(void *first, void *second) {
    int *island_array1 = (int *)first;
    int *island_array2 = (int *)second;
    int index = 0;
    while (island_array1[index] != -1 && island_array2[index] != -1) {
        if (island_array1[index] != island_array2[index]) {
            return island_array1[index] > island_array2[index]; 
        }
        index++;
    }
    
    return island_array1[index] > island_array2[index];
}

void get_path_indices(t_list **paths, t_list **parent, char **islands, int *buffer, int current_index, const int current, int source) {
    if (current == source) {
        int *result_array = malloc(current_index * sizeof(int));
        int j = 0;

        buffer[current_index++] = source; 
        for (int i = current_index - 2; i >= 0; i--) {
            result_array[j++] = buffer[i];
        }

        mx_push_back(&paths[buffer[1]], result_array); 
    } else {
        for (t_list *node = parent[current]; node; node = node->next) {
            buffer[current_index++] = *(int *)node->data;
            get_path_indices(paths, parent, islands, buffer, current_index, *(int *)node->data, source); 
            current_index--; 
        }
    }
}

void *get_index_island(char **islands, int index, int total) {
    if (index < 0 || index >= total) {
        return NULL; 
    }

    return islands[index]; 
}

void show_distance(int **graph, int *indices, int distance) {
    int current = 0;
    int next = 1;
    int path_count = 0;

    mx_printint(graph[indices[current]][indices[next]]);
    current++;
    next++;

    while (indices[next] != -1) {
        mx_printstr(" + ");
        mx_printint(graph[indices[current]][indices[next]]);
        current++;
        next++;
        path_count++;
    }

    if (path_count > 0) {
        mx_printstr(" = ");
        mx_printint(distance);
    }

    mx_printstr("\n"); 
}

void show_route(char **islands, int *path, int total_size) {
    int index = 0; 
    while (path[index + 1] != -1) {
        mx_printstr(get_index_island(islands, path[index], total_size)); 
        mx_printstr(" -> "); 
        index++; 
    }
    mx_printstr(get_index_island(islands, path[index], total_size));
}

void show_path(char **islands, int *path, int destination_index, int total_size) {
    mx_printstr(get_index_island(islands, path[0], total_size));
    mx_printstr(" -> "); 
    mx_printstr(get_index_island(islands, path[destination_index], total_size));
}

void print(int *distances, int source, int total_size, int **graph, char **islands, t_list **parent) {
    int index = 0;
    int *route_numbers = malloc(total_size * total_size * sizeof(int));
    t_list **paths_list = malloc((total_size + 1) * sizeof(t_list *));
    
    for (int i = 0; i < total_size; i++) {
        paths_list[i] = mx_create_node(malloc(sizeof(int)));
    }
    
    paths_list[total_size] = NULL; 

    for (int i = 0; i < total_size; i++) {
        if (i != source) {
            route_numbers[0] = -1; 
            route_numbers[1] = i;   
            get_path_indices(paths_list, parent, islands, route_numbers, 2, i, source);
            free(paths_list[i]->data); 
            mx_pop_front(&paths_list[i]); 
        }
    }
    for (int i = 1; paths_list[i]; i++) {
        if (i != source) {
            mx_sort_list(paths_list[i], compare_islands); 
            
            for (t_list *current_path = paths_list[i]; current_path; current_path = current_path->next) {
                int *routes = current_path->data;
                
                for (index = 0; routes[index + 1] != -1; index++);
                
                if (routes[index] > source) {
                    mx_printstr("========================================");
                    mx_printstr("\nPath: ");
                    show_path(islands, routes, index, total_size);
                    mx_printstr("\nRoute: ");
                    show_route(islands, routes, total_size);
                    mx_printstr("\nDistance: ");
                    show_distance(graph, routes, distances[i]);
                    mx_printstr("========================================");
                    mx_printstr("\n");
                }
            }
        }
    }
    
    free(route_numbers);
    for (int i = 0; i < total_size; i++) {
        delete_linked(&paths_list[i]); 
    }
    
    free(paths_list); 
}

