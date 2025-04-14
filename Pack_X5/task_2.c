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

void BFS(int start_v, int n, Node **adj, int *dist, int *queue) {
    for (int i = 1; i <= n; i++) dist[i] = -1;

    dist[start_v] = 0;
    int first = 0, last = 0;
    queue[last++] = start_v;

    while (first < last) {
        int u = queue[first++];

        for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->to;

            if (dist[v] == -1) {
                queue[last++] = v;
                dist[v] = dist[u] + 1;
            }
        }
    }
}

void free_graph(int n, Node **adj) {
    for (int i = 1; i <= n; i++) {
        Node *cur = adj[i];
        while (cur != NULL) {
            Node *temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    Node **adj = (Node **) calloc(n + 1, sizeof(Node *));
    int *dist = (int *) malloc((n + 1) * sizeof(int));
    int *queue = (int *) malloc((n + 1) * sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, adj);
    }

    BFS(1, n, adj, dist, queue);

    for (int i = 1; i <= n; i++) {
        printf("%d\n", dist[i]);
    }

    free_graph(n, adj);
    free(adj);
    free(dist);
    free(queue);

    return 0;
}