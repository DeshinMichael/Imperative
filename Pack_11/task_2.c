#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int value;
    struct Node_t* next;
} Node;

typedef void (*callback)(void *ctx, int *value);

void sum_even(void *ctx, int *value) {
    if (*value % 2 == 0) (*(int *)ctx) += *value;
}

void free_node(void *ctx, int *value) {
    Node *temp = (Node *)value;
    free(temp);
}

void arrayForeach(void *ctx, void func(void *ctx, int *value), int *arr, int n) {
    for (int i = 0; i < n; i++) {
        func(ctx, &arr[i]);
    }
}

void listForeach(void *ctx, void func(void *ctx, int *value), Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        func(ctx, (int *)temp);
    }
}

void initList(Node **head, int value, Node **last_node) {
    *head = (Node *) malloc(sizeof(Node));
    (*head)->value = value;
    (*head)->next = NULL;
    *last_node = *head;
}

void insertNode(Node **last_node, int value) {
    (*last_node)->next = (Node *) malloc(sizeof(Node));
    (*last_node)->next->value = value;
    (*last_node)->next->next = NULL;
    *last_node = (*last_node)->next;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int temp;
    scanf("%d", &temp);

    int *arr = (int *) malloc(n * sizeof(int));
    arr[0] = temp;

    Node *head;
    Node *last_node;
    initList(&head, temp, &last_node);

    for (int i = 1; i < n; i++) {
        scanf("%d", &temp);
        arr[i] = temp;
        insertNode(&last_node, temp);
    }

    int sum_in_arr = 0;
    int sum_in_list = 0;
    
    arrayForeach((void *)&sum_in_arr, sum_even, arr, n);
    listForeach((void *)&sum_in_list, sum_even, head);

    printf("%d %d", sum_in_arr, sum_in_list);

    free(arr);
    listForeach((void *)&sum_in_list, free_node, head);

    return 0;
}