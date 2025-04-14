#include <stdio.h>
#include <stdlib.h>

void DFS(int x, int y, int n, char **lab, char **visited) {
    if (x < 0 || x >= n || y < 0 || y >= n) return;
    if (lab[x][y] == '*' || visited[x][y]) return;

    visited[x][y] = 1;

    DFS(x-1, y, n, lab, visited);
    DFS(x+1, y, n, lab, visited);
    DFS(x, y-1, n, lab, visited);
    DFS(x, y+1, n, lab, visited);
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d\n", &n);

    char **lab = (char **) malloc(n * sizeof(char *));
    char **visited = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        lab[i] = (char *) malloc((n+2) * sizeof(char));
        visited[i] = (char *) calloc(n, sizeof(char));
    }

    for (int i = 0; i < n; i++) {
        fgets(lab[i], n+2, stdin);
    }

    int start_i = -1;
    for (int i = 0; i < n; i++) {
        if (lab[0][i] == ' ') {
            start_i = i;
            break;
        }
    }

    DFS(0, start_i, n, lab, visited);

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (lab[i][j] == ' ' && !visited[i][j]) {
                DFS(i, j, n, lab, visited);
                res++;
            }
        }
    }

    printf("%d", res);

    for (int i = 0; i < n; i++) {
        free(lab[i]);
        free(visited[i]);
    }
    free(lab);
    free(visited);

    return 0;
}