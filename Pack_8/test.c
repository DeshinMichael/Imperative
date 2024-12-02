#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

typedef struct Node {
    struct Node *prev, *next;
    double value;
} Node;

Node *getNodePtrFromValuePtr1(double *value) {
    return (Node *)((char *)value - offsetof(Node, value));
}

Node *getNodePtrFromValuePtr2(double *value) {
    return (Node *)((double *)value - offsetof(Node, value));
}

int main() {
    freopen("input.txt", "r", stdin);

    Node node1;
    node1.value = 7;

    Node *node_ptr1 = getNodePtrFromValuePtr1(&node1.value);
    Node *node_ptr2 = getNodePtrFromValuePtr2(&node1.value);

    printf("%p %p\n", &node1.value, node_ptr1);
    printf("%p %p\n", &node1.value, node_ptr2);

    return 0;
}