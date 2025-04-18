#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    if (list == NULL)
        return;

    t_list *new_node = mx_create_node(data);

    if (new_node == NULL)
        return; 

    new_node->next = *list; 

    *list = new_node; 
}
