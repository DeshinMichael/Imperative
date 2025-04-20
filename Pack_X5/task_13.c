#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;
const ll INF = LLONG_MAX / 2;

typedef struct Node_t {
    int to, cost, id;
    struct Node_t* next;
} Node;

typedef struct HeapNode_t {
    int v;
    ll dist;
} HeapNode;

void add_edge(int u, int v, int cost, int id, Node **adj) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->to = v;
    new_node->cost = cost;
    new_node->id = id;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void swap(int i, int j, HeapNode *heap, int *pos) {
    HeapNode tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;

    int pos_i = heap[i].v;
    int pos_j = heap[j].v;

    int t = pos[pos_i];
    pos[pos_i] = pos[pos_j];
    pos[pos_j] = t;
}

void heapify_up(int i, HeapNode *heap, int *pos) {
    while (i > 0) {
        int par = (i - 1) / 2;

        if (heap[par].dist <= heap[i].dist) break;

        swap(i, par, heap, pos);
        i = par;
    }
}

void heapify_down(int i, HeapNode *heap, int *heap_size, int *pos) {
    while (2 * i + 1 < *heap_size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int cur = i;

        if (heap[left].dist < heap[cur].dist) cur = left;
        if (right < *heap_size && heap[right].dist < heap[cur].dist) cur = right;

        if (cur == i) break;

        swap(i, cur, heap, pos);
        i = cur;
    }
}

void heap_push(int v, ll dist, HeapNode *heap, int *heap_size, int *pos) {
    if (pos[v] != -1) {
        if (dist < heap[pos[v]].dist) {
            heap[pos[v]].dist = dist;
            heapify_up(pos[v], heap, pos);
        }
        return;
    }
    heap[*heap_size].v = v;
    heap[*heap_size].dist = dist;
    pos[v] = *heap_size;
    (*heap_size)++;
    heapify_up(pos[v], heap, pos);
}

int heap_pop(HeapNode *heap, int *heap_size, int *pos) {
    int v = heap[0].v;
    pos[v] = -1;
    heap[0] = heap[--(*heap_size)];
    if (*heap_size > 0) {
        pos[heap[0].v] = 0;
        heapify_down(0, heap, heap_size, pos);
    }
    return v;
}

int heap_empty(int *heap_size) {
    return *heap_size == 0;
}

void dijkstra(int s, int N, Node **adj, HeapNode *heap, ll *dist, int *parent, int *edge_id, int *pos) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        parent[i] = -1;
        edge_id[i] = -1;
        pos[i] = -1;
    }

    int heap_size = 0;
    dist[s] = 0;
    heap_push(s, 0, heap, &heap_size, pos);

    while (!heap_empty(&heap_size)) {
        int u = heap_pop(heap, &heap_size, pos);
        for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->to;
            int cost = cur->cost;
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                parent[v] = u;
                edge_id[v] = cur->id;
                heap_push(v, dist[v], heap, &heap_size, pos);
            }
        }
    }
}

void print_path(int t, int N, ll *dist, int *parent, int *edge_id) {
    int *path = (int *) malloc((N+1) * sizeof(int));
    int k = 0;
    for (int v = t; parent[v] != -1; v = parent[v]) {
        path[k++] = edge_id[v];
    }

    printf("quarantine %lld %d", dist[t], k);
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

    Node **adj = (Node **) calloc(N + 1, sizeof(Node *));
    int **queries = (int **) malloc(K * sizeof(int *));
    ll *dist = (ll *) malloc((N + 1) * sizeof(ll));
    int *parent = (int *) malloc((N + 1) * sizeof(int));
    int *edge_id = (int *) malloc((N + 1) * sizeof(int));
    int *pos = (int *) malloc((N + 1) * sizeof(int));
    HeapNode *heap = (HeapNode *) malloc((2 * N + 10) * sizeof(HeapNode));

    for (int i = 0; i < K; i++) {
        queries[i] = (int *) malloc(2 * sizeof(int));
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    for (int i = 1; i <= M; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        add_edge(u, v, cost, i, adj);
    }

    for (int i = 0; i < K; i++) {
        int a = queries[i][0];
        int b = queries[i][1];

        dijkstra(a, N, adj, heap, dist, parent, edge_id, pos);

        if (dist[b] == INF) {
            printf("DOOMED\n");
        } else {
            print_path(b, N, dist, parent, edge_id);
        }
    }

    free_graph(N, adj);
    free(adj);
    for (int i = 0; i < K; i++) free(queries[i]);
    free(queries);
    free(dist);
    free(parent);
    free(edge_id);
    free(pos);
    free(heap);

    return 0;
}