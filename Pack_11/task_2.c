#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int value;
    int next;
} Node;

typedef void (*callback) (void *ctx, int *value);

void sum_even(void *ctx, int *value) {
    if (*value % 2 == 0) (*(int *)ctx) += *value;
}

void arrayForeach(void *ctx, callback func, int *arr, int n) {
    for (int i = 0; i < n; i++) {
        func(ctx, &arr[i]);
    }
}

void listForeach(void *ctx, callback func, Node *list, int n) {
    for (int i = 0; i != -1; i = list[i].next) {
        func(ctx, &list[i].value);
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int *arr = (int *) malloc(n * sizeof(int));
    Node *list = (Node *) malloc(n * sizeof(Node));

    int temp;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);

        arr[i] = temp;

        list[i].value = temp;
        list[i].next = (i == n-1) ? (-1) : i+1;
    }

    int sum_in_arr = 0;
    int sum_in_list = 0;
    
    arrayForeach((void *)&sum_in_arr, sum_even, arr, n);
    listForeach((void *)&sum_in_list, sum_even, list, n);

    printf("%d %d", sum_in_arr, sum_in_list);

    free(arr);
    free(list);

    return 0;
}