#include "libmx.h"

t_list *mx_create_node(void *data) {
    if (!data) 
        return NULL;

    t_list *node = (t_list *)malloc(sizeof(t_list)); 
    if (!node) return NULL; 
    
    node->data = data; 
    node->next = NULL;
    return node;
}
