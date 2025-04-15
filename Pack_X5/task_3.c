#include <stdio.h>
#include <stdlib.h>

typedef struct Point_t {
    int x, y;
} Point;

int BFS(Point s, Point f, int N, int M, char **lab, int **dist, int **visited, Point *queue, 
    int dx[], int dy[]) {
    int first = 0, last = 0;

    queue[last++] = s;
    visited[s.x][s.y] = 1;
    dist[s.x][s.y] = 0;

    while (first < last) {
        Point p = queue[first++];

        if (p.x == f.x && p.y == f.y) {
            return dist[p.x][p.y];
        }

        for (int d = 0; d < 4; d++) {
            int nx = p.x + dx[d];
            int ny = p.y + dy[d];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N &&
            !visited[nx][ny] && (lab[nx][ny] == '.' || lab[nx][ny] == 'F')) {

                visited[nx][ny] = 1;
                dist[nx][ny] = dist[p.x][p.y] + 1;
                queue[last].x = nx;
                queue[last++].y = ny;
            }
        }
    }

    return -1;
}

int main() {
    freopen("input.txt", "r", stdin);

    int M, N;
    scanf("%d %d", &M, &N);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    char **lab = (char **) malloc(M * sizeof(char *));
    int **dist = (int **) malloc(M * sizeof(int *));
    int **visited = (int **) malloc(M * sizeof(int *));
    Point *queue = (Point *) malloc(M * N * sizeof(Point));

    for (int i = 0; i < M; i++) {
        lab[i] = (char *) malloc((N+1) * sizeof(char));
        dist[i] = (int *) calloc(N, sizeof(int));
        visited[i] = (int *) calloc(N, sizeof(int));
    }

    Point s, f;
    for (int i = 0; i < M; i++) {
        scanf("%s", lab[i]);
        for (int j = 0; j < N; j++) {
            if (lab[i][j] == 'S') {
                s.x = i;
                s.y = j;
            }
            if (lab[i][j] == 'F') {
                f.x = i;
                f.y = j;
            }
        }
    }

    int res = BFS(s, f, N, M, lab, dist, visited, queue, dx, dy);
    printf("%d", res);

    for (int i = 0; i < M; i++) {
        free(lab[i]);
        free(dist[i]);
        free(visited[i]);
    }
    free(lab);
    free(dist);
    free(visited);
    free(queue);

    return 0;
}