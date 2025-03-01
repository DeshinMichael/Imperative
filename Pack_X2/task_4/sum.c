#include <stdint.h>

extern int64_t *arr;

void Init(int64_t *arr, int n) {
    for (int i = 1; i < n; i++) {
        arr[i] += arr[i-1];
    }
}

int64_t Sum(int l, int r) {
    if (r == 0) {
        return 0;
    }
    if (l == 0) {
        return arr[r-1];
    } else {
        return (arr[r-1] - arr[l-1]);
    }
}