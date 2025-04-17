#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int to;
    struct Node_t* next;
} Node;

void add_edge(int u, int v, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void DFS_1(int u, Node **adj, int *visited, int *tout, int *timer) {
    visited[u] = 1;
    for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
        int v = cur->to;
        if (!visited[v]) {
            DFS_1(v, adj, visited, tout, timer);
        }
    }
    tout[(*timer)++] = u; 
}

void DFS_2(int u, Node **adj_rev, int *visited, int *component, int *color) {
    visited[u] = 1;
    component[u] = *color;
    for (Node *cur = adj_rev[u]; cur != NULL; cur = cur->next) {
        int v = cur->to;
        if (!visited[v]) {
            DFS_2(v, adj_rev, visited, component, color);
        }
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
    Node **adj_rev = (Node **) calloc(N+1, sizeof(Node *));
    int *visited = (int *) calloc((N + 1), sizeof(int));
    int *tout = (int *)malloc((N + 1) * sizeof(int));
    int *component = (int *)malloc((N + 1) * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, adj);
        add_edge(v, u, adj_rev);
    }

    int timer = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) DFS_1(i, adj, visited, tout, &timer);
    }

    for (int i = 0; i <= N; i++) visited[i] = 0;

    int color = 1;
    for (int i = timer-1; i >= 0; i--) {
        int u = tout[i];
        if (!visited[u]) {
            DFS_2(u, adj_rev, visited, component, &color);
            color++;
        }
    }

    printf("%d\n", color-1);
    for (int i = 1; i <= N; i++) {
        printf("%d ", component[i]);
    }

    free_graph(N, adj);
    free_graph(N, adj_rev);
    free(adj);
    free(adj_rev);
    free(visited);
    free(tout);
    free(component);

    return 0;
}