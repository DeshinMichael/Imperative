#include <stdio.h>

#define MAX_N 2000

int C[MAX_N+1][MAX_N+1];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, t, n, k;
    scanf("%d %d", &m, &t);

    C[0][0] = 1;
    for (int n = 1; n < MAX_N+1; n++) {
        C[n][0] = 1;
        C[n][n] = 1;
        for (int k = 1; k < n; k++) {
            C[n][k] = (C[n-1][k-1] + C[n-1][k]) % m;
        }
    }

    for (int i = 0; i < t; i++) {
        scanf("%d %d", &n, &k);

        if (k < 0 || k > n) {
            printf("0\n");
        } else {
            printf("%d\n", C[n][k]);
        }
    }

    return 0;
}