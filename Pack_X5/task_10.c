#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int to, id;
    struct Node_t* next;
} Node;

typedef struct Pair_t {
    int a, b, id;
} Pair;

int cmp_pair(const void *x, const void *y) {
    const Pair *p = x;
    const Pair *q = y;
    if (p->a != q->a) return p->a - q->a;
    return p->b - q->b;
}

int cmp_int(const void *x, const void *y) {
    return *(const int*)x - *(const int*)y;
}

void add_edge(int u, int v, int id, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->id = id;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void DFS(int v, int par_id, Node **adj, int *visited, int *tin, int *up, 
    int *timer, int *single, int *bridges, int *bridge_cnt) {
    visited[v] = 1;
    tin[v] = up[v] = (*timer)++;

    for (Node *cur = adj[v]; cur != NULL; cur = cur->next) {
        int u = cur->to;
        int id = cur->id;

        if (id == par_id) continue;

        if (visited[u]) {
            if (tin[u] < up[v]) up[v] = tin[u];
        } else {
            DFS(u, id, adj, visited, tin, up,
                timer, single, bridges, bridge_cnt);

            if (up[u] < up[v]) up[v] = up[u];

            if (single[id] && up[u] > tin[v]) {
                bridges[(*bridge_cnt)++] = id;
            }
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

    int *U = (int *) malloc((M+1) * sizeof(int));
    int *V = (int *) malloc((M+1) * sizeof(int));
    Pair *pairs = (Pair *) malloc(M * sizeof(Pair));
    int *single = (int *) calloc(M+1, sizeof(int));
    Node **adj = (Node **) calloc(N+1, sizeof(Node *));
    int *visited = (int *) calloc(N+1, sizeof(int));
    int *tin = (int *) malloc((N+1) * sizeof(int));
    int *up = (int *) malloc((N+1) * sizeof(int));
    int *bridges = (int *) malloc(M * sizeof(int));

    int pair_cnt = 0;
    for (int id = 1; id <= M; id++) {
        int u, v;
        scanf("%d %d", &u, &v);
        U[id] = u;
        V[id] = v;

        if (u == v) continue;

        int a = u < v ? u : v;
        int b = u > v ? u : v;

        pairs[pair_cnt].a = a;
        pairs[pair_cnt].b = b;
        pairs[pair_cnt].id = id;
        pair_cnt++;
    }

    qsort(pairs, pair_cnt, sizeof(Pair), cmp_pair);
    for (int i = 0; i < pair_cnt;) {
        int j = i + 1;
        while (j < pair_cnt && pairs[j].a == pairs[i].a && pairs[j].b == pairs[i].b) {
            j++;
        }
        if (j - i == 1) single[pairs[i].id] = 1;
        i = j;
    }

    for (int id = 1; id <= M; id++) {
        int u = U[id];
        int v = V[id];
        if (u == v) continue;
        add_edge(u, v, id, adj);
        add_edge(v, u, id, adj);
    }

    int bridge_cnt = 0, timer = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            DFS(i, -1, adj, visited, tin, up,
                &timer, single, bridges, &bridge_cnt);
        }
    }

    qsort(bridges, bridge_cnt, sizeof(int), cmp_int);

    printf("%d\n", bridge_cnt);
    for (int i = 0; i < bridge_cnt; i++) {
        printf("%d ", bridges[i]);
    }

    free_graph(N, adj);
    free(adj);
    free(U);
    free(V);
    free(pairs);
    free(single);
    free(visited);
    free(tin);
    free(up);
    free(bridges);

    return 0;
}