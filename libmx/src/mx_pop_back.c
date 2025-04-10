#include "libmx.h"

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL) {
        return; 
    }

    t_list *current = *head;
    t_list *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        free(*head);
        *head = NULL;
    } else {
        prev->next = NULL;
        free(current);
    }
}
