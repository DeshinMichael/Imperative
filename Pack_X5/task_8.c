#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Node_t {
    int to, weight;
    struct Node_t* next;
} Node;

typedef struct Query_t {
    int s, t;
} Query;

void add_edge(int u, int v, int w, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->weight = w;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void dijkstra(int s, int N, Node **adj, int *dist, int *parent) {
    int *mark = (int *) calloc(N + 1, sizeof(int));
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
    free(mark);
}

void print_path(int t, int N, int *dist, int *parent) {
    int *path = (int *) malloc(N * sizeof(int));
    int k = 0;
    for (int v = t; v != -1; v = parent[v]) {
        path[k++] = v;
    }

    printf("%d", k);
    for (int i = k - 1; i >= 0; i--) {
        printf(" %d", path[i]);
    }
    printf("\n");

    free(path);
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

    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    Query *queries = (Query *) malloc(K * sizeof(Query));
    Node **adj = (Node **) calloc(N+1, sizeof(Node *));
    int *dist = (int *) malloc((N + 1) * sizeof(int));
    int *parent = (int *)malloc((N + 1) * sizeof(int));

    for (int i = 0; i < K; i++) {
        scanf("%d %d", &queries[i].s, &queries[i].t);
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, adj);
        add_edge(v, u, w, adj);
    }

    for (int i = 0; i < K; i++) {
        int s = queries[i].s;
        int t = queries[i].t;

        dijkstra(s, N, adj, dist, parent);

        if (dist[t] == INF) {
            printf("NO\n");
        } else {
            printf("YES %d ", dist[t]);
            print_path(t, N, dist, parent);
        }
    }

    free_graph(N, adj);
    free(adj);
    free(queries);
    free(dist);
    free(parent);

    return 0;
}