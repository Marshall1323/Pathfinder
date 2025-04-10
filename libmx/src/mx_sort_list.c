#include "libmx.h"

static void swap(void **s1, void **s2) {
    void *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (!lst || !cmp)
        return lst;

    bool swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    do {
        swapped = false;
        ptr1 = lst;

        while (ptr1->next != lptr) {
            if (cmp(ptr1->data, ptr1->next->data)) {
                swap(&ptr1->data, &ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return lst;
}
