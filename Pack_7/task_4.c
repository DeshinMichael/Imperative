#include <stdio.h>
#include <stdlib.h>

int bin_search_most_close(int *arr, int *sub, int num, int n) {
    if (num < arr[0]) {
        *sub = arr[0]-num;
        return 0;
    } else if (num > arr[n-1]) {
        *sub = num-arr[n-1];
        return n-1;
    }

    int left = 0;
    int right = n-1;
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == num) {
            *sub = 0;
            return mid;
        } else if (num < arr[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (num-arr[right] < arr[left]-num) {
        *sub = num-arr[right];
        return right;
    } else {
        *sub = arr[left]-num;
        return left;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int q;
    scanf("%d", &q);

    int y, sub, i_most_close;
    for (int i = 0; i < q; i++) {
        scanf("%d", &y);

        i_most_close = bin_search_most_close(arr, &sub, y, n);

        printf("%d %d\n", i_most_close, sub);
    }

    free(arr);

    return 0;
}