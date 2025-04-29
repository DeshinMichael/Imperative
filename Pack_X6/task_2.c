#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    freopen("input.txt", "r", stdin);

    int N;
    scanf("%d", &N);

    int **res = (int **) malloc((N+1) * sizeof(int *));
    for (int i = 0; i <= N; i++) {
        res[i] = (int *) malloc((N+1) * sizeof(int));
    }

    for (int sum = N; sum >= 0; sum--) {
        for (int last = 0; last <= N; last++) {
            if (sum == N) {
                res[sum][last] = 1;
            } else {
                res[sum][last] = 0;
                for (int x = 1; x <= last && x <= N - sum; x++) {
                    res[sum][last] = (res[sum][last] + res[sum + x][x]) % MOD;
                }
            }
        }
    }

    printf("%d\n", res[0][N]);

    for (int i = 0; i <= N; i++) {
        free(res[i]);
    }
    free(res);

    return 0;
}