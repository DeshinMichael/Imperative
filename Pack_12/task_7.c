#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int *deque = (int *) malloc(n * sizeof(int));
    int front = 0, back = 0; 

    int left = 0, right = 0;
    char q;
    scanf("%c", &q);

    for (int i = 0; i < (2*n-1); i++) {
        scanf("%c", &q);

        if (q == 'R') {
            while (back > front && arr[deque[back-1]] <= arr[right]) {
                back--;
            }
            deque[back++] = right;
            right++;
            printf("%d\n", arr[deque[front]]);
        } else {
            if (deque[front] == left) {
                front++;
            }
            left++;
            printf("%d\n", arr[deque[front]]); 
        }
    }

    free(arr);
    free(deque);

    return 0;
}