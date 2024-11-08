#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    struct Node *prev, *next;
    double value;
} Node;

Node *getNodePtrFromValuePtr(double *value) {
    return (Node *)((char *)value - offsetof(Node, value));
}

double *initList() {
    Node *head = (Node *) malloc(sizeof(Node));

    head->prev = head;
    head->next = head;

    return &head->value;
}

void freeList(double *head) {
    Node *head_node = getNodePtrFromValuePtr(head);
    Node *curr_node = head_node->next;

    while (curr_node != head_node) {
        Node *next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }

    free(head_node);
}

double *getNext(double* curr) {
    Node *curr_node = getNodePtrFromValuePtr(curr);
    return &curr_node->next->value;
}

double *getPrev(double* curr) {
    Node *curr_node = getNodePtrFromValuePtr(curr);
    return &curr_node->prev->value;
}

double *addAfter(double* where, double newval) {
    Node *curr_node = getNodePtrFromValuePtr(where);
    Node *new_node = (Node *) malloc(sizeof(Node));

    new_node->value = newval;
    new_node->next = curr_node->next;
    new_node->prev = curr_node;

    curr_node->next->prev = new_node;
    curr_node->next = new_node;
    return &new_node->value;
}

double *addBefore(double* where, double newval) {
    Node *curr_node = getNodePtrFromValuePtr(where);
    Node *new_node = (Node *) malloc(sizeof(Node));

    new_node->value = newval;
    new_node->prev = curr_node->prev;
    new_node->next = curr_node;

    curr_node->prev->next = new_node;
    curr_node->prev = new_node;
    return &new_node->value;
}

void erase(double* what) {
    Node *del_node = getNodePtrFromValuePtr(what);

    del_node->prev->next = del_node->next;
    del_node->next->prev = del_node->prev;

    free(del_node);
}

void printList(double *head_val) {
    for (double *i = getNext(head_val); i != head_val; i = getNext(i)) {
        printf("%0.3lf\n", *i);
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    double *head_val;
    double **list;

    int t, q;
    scanf("%d", &t);

    int oper, curr_i;
    double new_val;
    int cnt;
    for (int i = 0; i < t; i++) {
        scanf("%d", &q);

        head_val = initList();
        list = (double **) malloc(q * sizeof(double *));
        cnt = 0;

        for (int i = 0; i < q; i++) {
            scanf("%d", &oper);

            switch (oper) {
                case 1:
                    scanf("%d %lf", &curr_i, &new_val);
                    if (curr_i == -1) list[cnt] = addAfter(head_val, new_val);
                    else list[cnt] = addAfter(list[curr_i], new_val);
                    cnt++;
                    break;
                case -1:
                    scanf("%d %lf", &curr_i, &new_val);
                    if (curr_i == -1) list[cnt] = addBefore(head_val, new_val);
                    else list[cnt] = addBefore(list[curr_i], new_val);
                    cnt++;
                    break;
                case 0:
                    scanf("%d", &curr_i);
                    printf("%0.3lf\n", *list[curr_i]);
                    erase(list[curr_i]);
                    break;
            }
        }

        printf("===\n");
        printList(head_val);
        printf("===\n");

        freeList(head_val);
        free(list);
    }

    return 0;
}