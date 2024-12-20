#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int bin_search(int *arr, int num, int left, int right) {
    int mid, result = -1;
    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == num) {
            result = mid;
            left = mid + 1;
        }
        if (arr[mid] < num) {
            left = mid + 1;
        }
        if (arr[mid] > num) {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int arr[7] = {1, 2, 2, 3, 4, 5, 7};
    int i = bin_search(arr, 2, 0, 6);
    printf("%d", i);

    return 0;
}