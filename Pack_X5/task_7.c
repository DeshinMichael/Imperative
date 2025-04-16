#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Node_t {
    int to, weight;
    struct Node_t* next;
} Node;

void add_edge(int u, int v, int w, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->weight = w;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void belman_ford(int N, Node **adj, int *dist, int *parent) {
    int *queue = (int *) malloc(N * N * sizeof(int));
    int *mark = (int *) calloc(N+1, sizeof(int));

    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[1] = 0;
    int first = 0, last = 0;
    queue[last++] = 1;
    mark[1] = 1;

    while (first < last) {
        int u = queue[first++];
        mark[u] = 0;

        for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->to;
            int w = cur->weight;

            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!mark[v]) {
                    queue[last++] = v;
                    mark[v] = 1;
                }
            }
        }
    }

    free(queue);
    free(mark);
}

void print_path(int t, int N, int *dist, int *parent) {
    int *path = (int *) malloc(N * sizeof(int));
    int k = 0;
    for (int v = t; v != -1; v = parent[v]) {
        path[k++] = v;
    }

    printf("%d %d", dist[t], k);
    for (int i = k - 1; i >= 0; i--) {
        printf(" %d", path[i]);
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

    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int *friends = (int *) malloc(K * sizeof(int));
    Node **adj = (Node **) calloc(N+1, sizeof(Node *));
    int* dist = (int*)malloc((N + 1) * sizeof(int));
    int* parent = (int*)malloc((N + 1) * sizeof(int));

    for (int i = 0; i < K; i++) {
        scanf("%d", &friends[i]);
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, adj);
    }

    belman_ford(N, adj, dist, parent);

    for (int i = 0; i < K; i++) {
        print_path(friends[i], N, dist, parent);
    }

    free_graph(N, adj);
    free(adj);
    free(dist);
    free(parent);
    free(friends);

    return 0;
}