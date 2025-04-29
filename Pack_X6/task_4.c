#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int N;
    scanf("%d", &N);

    int *A = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int *len_p = (int *) malloc(N * sizeof(int));
    int *prev = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        len_p[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && len_p[j] + 1 > len_p[i]) {
                len_p[i] = len_p[j] + 1;
                prev[i] = j;
            }
        }
    }

    int max_len = 0, last = 0;
    for (int i = 0; i < N; i++) {
        if (len_p[i] > max_len) {
            max_len = len_p[i];
            last = i;
        }
    }

    int *res = (int *) malloc(max_len * sizeof(int));
    int *index = (int *) malloc(max_len * sizeof(int));
    int count = max_len - 1;
    for (int i = last; i != -1; i = prev[i]) {
        res[count] = A[i];
        index[count] = i + 1;
        count--;
    }

    printf("%d\n", max_len);
    for (int i = 0; i < max_len; i++) {
        printf("A[%d] = %d\n", index[i], res[i]);
    }

    free(A);
    free(len_p);
    free(prev);
    free(res);
    free(index);
    
    return 0;
}