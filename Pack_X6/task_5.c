#include <stdio.h>
#include <stdlib.h>

int DFS(int u, int B, int **graph, int *match_task, int *visited) {
    for (int v = 1; v <= B; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;
            if (match_task[v] == 0 || DFS(match_task[v], B, graph, match_task, visited)) {
                match_task[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    int A, B, M;
    scanf("%d %d %d", &A, &B, &M);

    int **graph = (int **) calloc(A+1, sizeof(int *));
    int *match_task = (int *) calloc(B+1, sizeof(int));

    for (int i = 0; i <= A; i++) {
        graph[i] = (int *) calloc(B+1, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    int res = 0;
    int *visited;
    for (int u = 1; u <= A; u++) {
        visited = (int *) calloc(B+1, sizeof(int));
        if (DFS(u, B, graph, match_task, visited)) {
            res++;
        }
    }

    printf("%d\n", res);
    for (int v = 1; v <= B; v++) {
        if (match_task[v] != 0) {
            printf("%d %d\n", match_task[v], v);
        }
    }

    for (int i = 0; i <= A; i++) {
        free(graph[i]);
    }
    free(graph);
    free(match_task);
    free(visited);

    return 0;
}