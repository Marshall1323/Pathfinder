#include "libmx.h"

int mx_quicksort(char **arr, int start, int end) {
    if (arr == NULL || start >= end) {
        return 0;
    }

    int swap_count = 0;
    int left = start;
    int right = end;
    char *pivot = arr[(left + right) / 2];

    while (left <= right) {
        while (mx_strlen(arr[left]) < mx_strlen(pivot)) {
            left++;
        }
        while (mx_strlen(arr[right]) > mx_strlen(pivot)) {
            right--;
        }

        if (left <= right) {
            if (mx_strlen(arr[left]) != mx_strlen(arr[right])) {
                char *temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
                swap_count++;
            }
            left++;
            right--;
        }
    }

    swap_count += mx_quicksort(arr, start, right);
    swap_count += mx_quicksort(arr, left, end);

    return swap_count;
}
