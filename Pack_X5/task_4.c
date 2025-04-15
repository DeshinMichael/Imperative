#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int to;
    struct Node_t* next;
} Node;

void add_edge(int u, int v, Node **adj, int *indeg) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->next = adj[u];
    adj[u] = new_node;
    indeg[v]++;
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

    Node **adj = (Node **) calloc((n+1), sizeof(Node *));
    int *indeg = (int *) calloc((n+1), sizeof(int));
    int *res = (int *) malloc((n+1) * sizeof(int));
    int *queue = (int *) malloc((n+1) * sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, adj, indeg);
    }

    int first = 0, last = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            queue[last++] = i;
        }
    }

    int value = 1;
    while (first < last) {
        int u = queue[first++];
        res[u] = value++;

        for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->to;
            indeg[v]--;
            if (indeg[v] == 0) {
                queue[last++] = v;
            }
        }
    }

    if (value <= n) {
        printf("NO");
        return 0;
    }

    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", res[i]);
    }

    free_graph(n, adj);
    free(adj);
    free(indeg);
    free(res);
    free(queue);

    return 0;
}