#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack_s {
    int *arr;
    int top;
    int *minStack;
    int *maxStack;
} Stack;

void init(Stack *stack, int n) {
    stack->arr = (int *) malloc(n * sizeof(int));
    stack->top = -1;
    stack->minStack = (int *) malloc(n * sizeof(int));
    stack->maxStack = (int *) malloc(n * sizeof(int));
}

void push(Stack *stack, int val) {
    stack->arr[++stack->top] = val;

    if (stack->top == 0 || val < stack->minStack[stack->top - 1]) {
        stack->minStack[stack->top] = val;
    } else {
        stack->minStack[stack->top] = stack->minStack[stack->top - 1];
    }

    if (stack->top == 0 || val > stack->maxStack[stack->top - 1]) {
        stack->maxStack[stack->top] = val;
    } else {
        stack->maxStack[stack->top] = stack->maxStack[stack->top - 1];
    }
}

int pop(Stack *stack) {
    return stack->arr[stack->top--];
}

int min(Stack *stack) {
    return stack->minStack[stack->top];
}

int max(Stack *stack) {
    return stack->maxStack[stack->top];
}

int main() {
    int n, val;
    char s[5];
    scanf("%d", &n);

    Stack stack;
    init(&stack, n);

    int *res = (int *) calloc(n, sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (strcmp(s, "push") == 0) {
            scanf("%d", &val);
            push(&stack, val);
        } else if (strcmp(s, "pop") == 0) {
            res[count] = pop(&stack);
            count++;
        } else if (strcmp(s, "min") == 0) {
            res[count] = min(&stack);
            count++;
        } else if (strcmp(s, "max") == 0) {
            res[count] = max(&stack);
            count++;
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("%d\n", res[i]);
    }

    free(res);
    free(stack.arr);

    return 0;
}