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

int DFS(int v, int *circle_s, int *circle_f, Node **adj, int *mark, int *parent) {
    mark[v] = 1;

    for (Node *cur = adj[v]; cur != NULL; cur = cur->next) {
        int u = cur->to;

        if (mark[u] == 0) {
            parent[u] = v;
            if (DFS(u, circle_s, circle_f, adj, mark, parent)) return 1;
        } else if (mark[u] == 1) {
            *circle_s = u;
            *circle_f = v;
            return 1;
        }
    }

    mark[v] = 2;
    return 0;
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

    int N, M;
    scanf("%d %d", &N, &M);

    Node **adj = (Node **) calloc((N+1), sizeof(Node *));
    int *mark = (int *) calloc((N+1), sizeof(int));
    int *parent = (int *) malloc((N+1) * sizeof(int));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, adj);
    }

    int circle_s = -1, circle_f = -1;
    for (int i = 1; i <= N; i++) {
        if (mark[i] == 0) {
            if (DFS(i, &circle_s, &circle_f, adj, mark, parent)) break;
        }
    }

    int *answer = (int *) malloc((N+1) * sizeof(int));

    if (circle_s == -1) {
        printf("-1");
    } else {
        int k = 0;
        answer[k++] = circle_s;
        for (int v = circle_f; v != circle_s; v = parent[v]) {
            answer[k++] = v;
        }

        printf("%d\n", k);
        for (int i = k-1; i >= 0; i--) {
            printf("%d ", answer[i]);
        }
    }

    free_graph(N, adj);
    free(adj);
    free(mark);
    free(parent);
    free(answer);

    return 0;
}