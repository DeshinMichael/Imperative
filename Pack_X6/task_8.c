#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int N, W;
    scanf("%d %d", &N, &W);

    int *weight = (int *) malloc(N * sizeof(int));
    int *cost = (int *) malloc(N * sizeof(int));
    int **dp = (int **) malloc((N+1) * sizeof(int *));
    int **take = (int **) malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &weight[i], &cost[i]);
    }

    for (int i = 0; i <= N; i++) {
        dp[i] = (int *) calloc(W+1, sizeof(int));
        if (i < N) {
            take[i] = (int *) calloc(W+1, sizeof(int));
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int w = 0; w <= W; w++) {
            int skip_it = dp[i+1][w];

            int take_it;
            if (weight[i] + w <= W) {
                take_it = dp[i+1][weight[i] + w] + cost[i];
            } else {
                take_it = -1;
            }

            if (take_it > skip_it) {
                dp[i][w] = take_it;
                take[i][w] = 1;
            } else {
                dp[i][w] = skip_it;
                take[i][w] = 0;
            }
        }
    }

    int total_w = 0;
    int total_c = 0;
    int *path = (int *) malloc(N * sizeof(int));
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (take[i][total_w]) {
            path[k++] = i + 1;
            total_w += weight[i];
            total_c += cost[i];
        }
    }

    printf("%d %d %d\n", k, total_w, total_c);
    for (int i = 0; i < k; i++) {
        printf("%d ", path[i]);
    }

    for (int i = 0; i <= N; i++) {
        free(dp[i]);
    }
    for (int i = 0; i < N; i++) {
        free(take[i]);
    }
    free(dp);
    free(take);
    free(weight);
    free(cost);
    free(path);

    return 0;
}