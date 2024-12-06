#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*callback) (const void *x, const void *y);

int cmp_long(const void *x, const void *y) {
    long long a = *(long long *)x;
    long long b = *(long long *)y;
    return a == b ? 0 : (a < b ? -1 : 1);
}

int cmp_string_sort(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int cmp_string_search(const void *key, const void *elem) {
    const char *str_key = (const char *)key;
    const char *str_elem = *(const char **)elem;
    return strcmp(str_key, str_elem);
}

void *lower_bound(const void *key, const void *base, int *n, size_t size, callback cmp, int *res) {
    int left = 0;
    int right = *n-1;
    *res = *n;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        const void *mid_elem = (const char *)base + mid * size;
        int cmp_res = cmp(key, mid_elem);

        if (cmp_res < 0) {
            right = mid - 1;
        } else if (cmp_res > 0) {
            left = mid + 1;
        } else {
            *res = mid;
            right = mid - 1;
        }
    }

    if (*res == *n) {
        *res = left;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n1;
    scanf("%d", &n1);
    long long *arr1 = (long long *) malloc(n1 * sizeof(long long));
    for (int i = 0; i < n1; i++) {
        scanf("%lld", &arr1[i]);
    }

    int n2;
    scanf("%d", &n2);
    char **arr2 = (char **) malloc(n2 * sizeof(char *));
    for (int i = 0; i < n2; i++) {
        arr2[i] = (char *) malloc(32 * sizeof(char));
        scanf("%s", arr2[i]);
    }

    qsort(arr1, n1, sizeof(arr1[0]), cmp_long);
    qsort(arr2, n2, sizeof(arr2[0]), cmp_string_sort);

    // for (int i = 0; i < n1; i++) {
    //     printf("%lld\n", arr1[i]);
    // }
    // for (int i = 0; i < n2; i++) {
    //     printf("%s\n", arr2[i]);
    // }

    int q1;
    scanf("%d", &q1);
    long long num;
    for (int i = 0; i < q1; i++) {
        scanf("%lld", &num);
        int res;
        lower_bound(&num, arr1, &n1, sizeof(arr1[0]), cmp_long, &res);
        printf("%d\n", res);
    }

    int q2;
    scanf("%d", &q2);
    char str[32];
    for (int i = 0; i < q2; i++) {
        scanf("%s", str);
        int res;
        lower_bound(str, arr2, &n2, sizeof(arr2[0]), cmp_string_search, &res);
        printf("%d\n", res);
    }

    free(arr1);
    for (int i = 0; i < n2; i++) {
        free(arr2[i]);
    }
    free(arr2);

    return 0;
}