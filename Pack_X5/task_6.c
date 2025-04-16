#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Node_t {
    int to, weight;
    struct Node_t* next;
} Node;

void add_edge(int u, int v, int weight, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->weight = weight;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void dijkstra(int s, int N, Node **adj, int *dist, int *parent, int *mark) {
    int *gray = (int *) malloc((N + 1) * sizeof(int));
    int gray_size = 0;

    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        parent[i] = -1;
        mark[i] = 0;
    }

    dist[s] = 0;
    gray[gray_size++] = s;
    mark[s] = 1;

    while (gray_size > 0) {
        int min_idx = 0;
        for (int i = 1; i < gray_size; i++) {
            if (dist[gray[i]] < dist[gray[min_idx]]) {
                min_idx = i;
            }
        }

        int u = gray[min_idx];
        gray[min_idx] = gray[--gray_size];
        mark[u] = 2;

        for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->to;
            int w = cur->weight;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (mark[v] == 0) {
                    gray[gray_size++] = v;
                    mark[v] = 1;
                }
            }
        }
    }

    free(gray);
}

void print_path(int t, int N, int *parent) {
    int *path = (int *) malloc(N * sizeof(int));
    int k = 0;
    for (int v = t; v != -1; v = parent[v]) {
        path[k++] = v;
    }

    printf("%d ", k);
    for (int i = k - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void free_graph(int n, Node **adj) {
    for (int i = 1; i <= n; i++) {
        Node *cur = adj[i];
        while (cur) {
            Node *temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int N, M, P, K;
    scanf("%d %d %d %d", &N, &M, &P, &K);

    Node **adj = (Node **) calloc(N + 1, sizeof(Node *));
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, adj);
        add_edge(v, u, w, adj);
    }

    int **dist_all = (int **) malloc((N + 1) * sizeof(int *));
    int **parent_all = (int **) malloc((N + 1) * sizeof(int *));
    int *mark = (int *) calloc(N + 1, sizeof(int));

    for (int i = 1; i <= N; i++) {
        dist_all[i] = (int *) malloc((N + 1) * sizeof(int));
        parent_all[i] = (int *) malloc((N + 1) * sizeof(int));
        dijkstra(i, N, adj, dist_all[i], parent_all[i], mark);
    }

    for (int i = 0; i < P; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%d ", dist_all[s][t]);
        print_path(t, N, parent_all[s]);
    }

    for (int i = 0; i < K; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%d\n", dist_all[s][t]);
    }

    for (int i = 1; i <= N; i++) {
        free(dist_all[i]);
        free(parent_all[i]);
    }
    free(dist_all);
    free(parent_all);
    free(mark);
    free_graph(N, adj);
    free(adj);

    return 0;
}
