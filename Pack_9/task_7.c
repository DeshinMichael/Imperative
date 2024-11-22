#include <stdio.h>
#include <stdlib.h>

long long argmin(long long *a, int i, int c) {
    return a[i] + (long long)c * i; 
}

int find_min(long long *a, int n, int c) {
    int left = 0;
    int right = n-1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (argmin(a, mid, c) > argmin(a, mid+1, c)) {
            left = mid+1;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, q;
    scanf("%d", &n);

    long long *a = (long long *) malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    scanf("%d", &q);
    int c;
    for (int i = 0; i < q; i++) {
        scanf("%d", &c);

        printf("%d\n", find_min(a, n, c));
    }

    free(a);

    return 0;
}