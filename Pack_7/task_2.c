#include <stdio.h>
#include <stdlib.h>

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
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int q;
    scanf("%d", &q);

    int x, y, r = 0;
    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        y = x + r;
        r = bin_search(arr, y, 0, n-1);
        printf("%d\n", r);
    }

    free(arr);

    return 0;
}