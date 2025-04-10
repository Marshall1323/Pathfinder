#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int count = 0;
    int i = 0;

    while (i < size) {
        if (arr[i] == NULL) {
            return -1;
        }

        int j = 0;
        while (j < size - 1) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                count++;
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    return count;
}
