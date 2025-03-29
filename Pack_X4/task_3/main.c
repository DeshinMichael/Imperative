#include "sol.h"
#include <assert.h>

int main() {
    init();
    assert(getEdgesCount(0) == 2);
    assert(getIncidentEdge(0, 0).weight == 178);
    assert(getIncidentEdge(0, 1).weight == 101);
    assert(getEdgesCount(1) == 4);
    assert(getIncidentEdge(1, 0).weight == 356);
    assert(getIncidentEdge(1, 3).weight == 213);
    assert(getIncidentEdge(1, 2).weight == 286);
    assert(getIncidentEdge(1, 1).weight == 356);
    assert(getEdgesCount(2) == 2);
    assert(getIncidentEdge(2, 0).weight == 178);
    assert(getIncidentEdge(2, 1).weight == 101);
    assert(getEdgesCount(3) == 1);
    assert(getIncidentEdge(3, 0).weight == 207);
    assert(getEdgesCount(4) == 3);
    assert(getIncidentEdge(4, 2).weight == 213);
    assert(getIncidentEdge(4, 0).weight == 207);
    assert(getIncidentEdge(4, 1).weight == 286);
    destroy();

    return 0;
}