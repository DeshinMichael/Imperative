#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

int BFS(int N, int s, int t, int **c, int **f, int *parent) {
    int *visited = (int *) calloc(N, sizeof(int));
    int *queue = (int *) malloc(N * sizeof(int));
    int first = 0, last = 0;

    visited[s] = 1;
    parent[s] = -1;
    queue[last++] = s;

    while (first < last) {
        int u = queue[first++];
        for (int v = 0; v < N; v++) {
            if (!visited[v] && c[u][v] - f[u][v] > 0) {
                parent[v] = u;
                visited[v] = 1;
                queue[last++] = v;
                if (v == t) {
                    free(visited);
                    free(queue);
                    return 1;
                }
            }
        }
    }

    free(visited);
    free(queue);
    return 0;
}

int Edmonds_Karp(int N, int s, int t, int **c, int **f) {
    int max_f = 0;
    int *parent = (int *) malloc(N * sizeof(int));

    while (BFS(N, s, t, c, f, parent)) {
        int path_f = INF;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int cf = c[u][v] - f[u][v];
            if (cf < path_f) {
                path_f = cf;
            }
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            f[u][v] += path_f;
            f[v][u] -= path_f;
        }

        max_f += path_f;
    }

    free(parent);
    return max_f;
}

int main() {
    freopen("input.txt", "r", stdin);

    int N, K;
    scanf("%d %d", &N, &K);

    int **cap = (int **) malloc(N * sizeof(int *));
    int **flow = (int **) malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        cap[i] = (int *) calloc(N, sizeof(int));
        flow[i] = (int *) calloc(N, sizeof(int));
    }

    for (int i = 0; i < K; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--;
        v--;
        cap[u][v] += c;
        cap[v][u] += c;
    }

    int s = 0, t = N - 1;
    int res = Edmonds_Karp(N, s, t, cap, flow);
    printf("%d\n", res);

    for (int i = 0; i < N; i++) {
        free(cap[i]);
        free(flow[i]);
    }
    free(cap);
    free(flow);

    return 0;
}