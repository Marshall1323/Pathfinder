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

static int find_index(int *distance, bool *visited, int size) {
    int minValue = INT_MAX;
    int indexOfMin = -1;
    for (int idx = 0; idx < size; idx++) {
        if (visited[idx] == false && distance[idx] < minValue) {
            minValue = distance[idx];
            indexOfMin = idx;
        }
    }
    return indexOfMin;
}


void create_matrix(int **Adj, int **arr, int N, int M, struct bridge *bridges) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            Adj[row][col] = 0;
        }
    }
    
    for (int bridge_idx = 0; bridge_idx < M; bridge_idx++) {
        int from = arr[bridge_idx][0];
        int to = arr[bridge_idx][1];

        int length = bridges[bridge_idx].len;
        Adj[from][to] = length;
        Adj[to][from] = length;
    }
}

int **create_graph(bridge *bridges, char *filename) {
    char *file_content = mx_file_to_str(filename);
    int graph_size = mx_atoi(&file_content[0]);
    file_content = remove_first_line(file_content);
    int bridge_count = mx_count_words(file_content, '\n');
    int **temp_edges = malloc(bridge_count * sizeof(int *));
    for (int edge_idx = 0; edge_idx < bridge_count; edge_idx++) {
        temp_edges[edge_idx] = malloc(2 * sizeof(int));
    }
    int **adjacency_matrix = malloc(graph_size * sizeof(int *));
    for (int node = 0; node < graph_size; node++) {
        adjacency_matrix[node] = malloc(graph_size * sizeof(int));
    }
    int *vertex_indices = malloc((bridge_count * 2) * sizeof(int));
    for (int idx = 0, bridge_idx = 0; idx < bridge_count * 2; bridge_idx++) {
        vertex_indices[idx++] = bridges[bridge_idx].src;
        vertex_indices[idx++] = bridges[bridge_idx].dest;
    }
    for (int edge_idx = 0, vertex_idx = 0; edge_idx < bridge_count; edge_idx++) {
        for (int vertex_pos = 0; vertex_pos < 2; vertex_pos++) {
            temp_edges[edge_idx][vertex_pos] = vertex_indices[vertex_idx++];
        }
    }

    create_matrix(adjacency_matrix, temp_edges, graph_size, bridge_count, bridges);

    for (int edge_idx = 0; edge_idx < bridge_count; edge_idx++) {
        free(temp_edges[edge_idx]);
    }
    free(temp_edges);
    free(vertex_indices);
    free(file_content);

    return adjacency_matrix;
}


void delete_list(t_list **list) {
    t_list *node = *list;
    
    while (node) {
        t_list *temp = node->next;
        free(node);
        node = temp;
    }

    *list = NULL;
}

void dijkstra(int **graph, int src, char *filename, struct bridge *bridges) {
    char *file_content = mx_file_to_str(filename);
    int graph_size = mx_atoi(&file_content[0]);
    int parent_count = 0;

    int *distances = malloc(graph_size * graph_size * sizeof(int));
    int *temp_parents = malloc(graph_size * graph_size * sizeof(int));

    file_content = remove_first_line(file_content);
    char **islands = read_islands(bridges, filename);

    bool *visited_nodes = malloc(graph_size * sizeof(bool));
    t_list **parents = malloc(graph_size * sizeof(t_list *));

    for (int i = 0; i < graph_size; i++) {
        distances[i] = INT_MAX;
        parents[i] = mx_create_node((void *)&src);
        visited_nodes[i] = false;
    }

    distances[src] = 0;

    for (int step = 0; step < graph_size - 1; step++) {
        int U = find_index(distances, visited_nodes, graph_size);
        visited_nodes[U] = true;
        for (int neighbor = 0; neighbor < graph_size; neighbor++) {
            if (!visited_nodes[neighbor] && graph[U][neighbor] && distances[U] + graph[U][neighbor] < distances[neighbor]) {
                temp_parents[parent_count] = U;
                distances[neighbor] = distances[U] + graph[U][neighbor];
                delete_list(&parents[neighbor]);
                mx_push_back(&parents[neighbor], (void *)&temp_parents[parent_count++]);
            }
            else if (!visited_nodes[neighbor] && graph[U][neighbor] && distances[U] + graph[U][neighbor] == distances[neighbor]) {
                temp_parents[parent_count] = U;
                mx_push_back(&parents[neighbor], (void *)&temp_parents[parent_count++]);
            }
        }
    }

    print(distances, src, graph_size, graph, islands, parents);

    for (int i = 0; i < graph_size; i++) {
        delete_list(&parents[i]);
        free(islands[i]);
    }

    free(distances);
    free(parents);
    free(temp_parents);
    free(visited_nodes);
    free(islands);
    free(file_content);
}
