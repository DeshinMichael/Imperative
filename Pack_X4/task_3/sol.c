#include "sol.h"
#include <stdlib.h>

typedef struct {
    Edge *edges;
    int count;
    int capacity;
} EdgeList;

static EdgeList *adj_lists = NULL;
static int k_vertex = 0;

void init() {
    k_vertex = getVerticesCount();
    adj_lists = (EdgeList *) calloc(k_vertex, sizeof(EdgeList));

    Edge edge;
    while (readEdge(&edge)) {
        if (adj_lists[edge.from].count == adj_lists[edge.from].capacity) {
            adj_lists[edge.from].capacity = adj_lists[edge.from].capacity * 2 + 4;
            adj_lists[edge.from].edges = (Edge *) realloc(adj_lists[edge.from].edges,
                adj_lists[edge.from].capacity * sizeof(Edge));
        }
        adj_lists[edge.from].edges[adj_lists[edge.from].count++] = edge;

        if (adj_lists[edge.to].count == adj_lists[edge.to].capacity) {
            adj_lists[edge.to].capacity = adj_lists[edge.to].capacity * 2 + 4;
            adj_lists[edge.to].edges = (Edge *) realloc(adj_lists[edge.to].edges,
                adj_lists[edge.to].capacity * sizeof(Edge));
        }

        Edge reverse_edge;
        reverse_edge.from = edge.to;
        reverse_edge.to = edge.from;
        reverse_edge.weight = edge.weight;

        adj_lists[edge.to].edges[adj_lists[edge.to].count++] = reverse_edge;
    }
}

void destroy() {
    if (adj_lists != NULL) {
        for (int i = 0; i < k_vertex; i++) {
            free(adj_lists[i].edges);
        }
        free(adj_lists);
        adj_lists = NULL;
    }
}

int getEdgesCount(int iVertex) {
    return adj_lists[iVertex].count;
}

Edge getIncidentEdge(int iVertex, int iIndex) {
    return adj_lists[iVertex].edges[iIndex];
}