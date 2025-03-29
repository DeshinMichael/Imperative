#include "sol.h"
#include <stdio.h>

// Пример: граф из 5 вершин и 6 рёбер
// Рёбра:
// [0, 2, 178]
// [3, 4, 207]
// [1, 1, 356]
// [2, 0, 101]
// [4, 1, 286]
// [4, 1, 213]

static Edge edgeList[] = {
    {0, 2, 178},
    {3, 4, 207},
    {1, 1, 356},
    {2, 0, 101},
    {4, 1, 286},
    {4, 1, 213}
};

static int edgeIndex = 0;

int getVerticesCount() {
    return 5;
}

int readEdge(Edge *oEdge) {
    if (edgeIndex < sizeof(edgeList)/sizeof(edgeList[0])) {
        *oEdge = edgeList[edgeIndex++];
        return 1;
    }
    return 0;
}