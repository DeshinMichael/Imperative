#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int to;
    struct Node_t* next;
} Node;

int cmp_int(const void *x, const void *y) {
    return *(const int*)x - *(const int*)y;
}

void add_edge(int u, int v, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void DFS(int v, int parent, Node **adj, int *visited, int *tin, int *up, 
    int *timer, int *art_dot) {
    visited[v] = 1;
    tin[v] = up[v] = (*timer)++;
    int k_child = 0;

    for (Node *cur = adj[v]; cur != NULL; cur = cur->next) {
        int u = cur->to;

        if (u == parent) continue;

        if (visited[u]) {
            if (tin[u] < up[v]) up[v] = tin[u];
        } else {
            DFS(u, v, adj, visited, tin, up,
                timer, art_dot);

            if (up[u] < up[v]) up[v] = up[u];

            if (up[u] >= tin[v] && parent != -1) {
                art_dot[v] = 1;
            }

            k_child++;
        }
    }

    if (parent == -1 && k_child > 1) {
        art_dot[v] = 1;
    }
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

    int N, M;
    scanf("%d %d", &N, &M);

    Node **adj = (Node **) calloc(N+1, sizeof(Node *));
    int *visited = (int *) calloc(N+1, sizeof(int));
    int *tin = (int *) calloc(N+1, sizeof(int));
    int *up = (int *) calloc(N+1, sizeof(int));
    int *art_dot = (int *) calloc(N+1, sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u != v) {
            add_edge(u, v, adj);
            add_edge(v, u, adj);
        }
    }

    int timer = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            DFS(i, -1, adj, visited, tin, up,
                &timer, art_dot);
        }
    }

    int *res = (int *) malloc((N+1) * sizeof(int));
    int k = 0;
    for (int i = 1; i <= N; i++) {
        if (art_dot[i]) res[k++] = i;
    }

    qsort(res, k, sizeof(int), cmp_int);

    printf("%d\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free_graph(N, adj);
    free(adj);
    free(visited);
    free(tin);
    free(up);
    free(art_dot);
    free(res);

    return 0;
}