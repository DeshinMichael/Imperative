#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x == y ? 0 : (x < y ? -1 : 1));
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int *a = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int m;
    scanf("%d", &m);

    int *b = (int *) malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    qsort(a, n, sizeof(int), cmp);
    qsort(b, m, sizeof(int), cmp);

    int res_k = 0;
    int *res;
    for (int i = 0; i < n-1; i++) {
        if (a[i] != a[i+1]) {
            res = (int *)bsearch(&a[i], b, m, sizeof(int), cmp);
            if (res == NULL) {
                a[res_k] = a[i];
                res_k++;
            }
        }
    }
    res = (int *) bsearch(&a[n-1], b, m, sizeof(int), cmp);
    if (res == NULL) {
        a[res_k] = a[n-1];
        res_k++;
    }

    printf("%d\n", res_k);
    for (int i = 0; i < res_k; i++) {
        printf("%d ", a[i]);
    }

    free(a);
    free(b);

    return 0;
}