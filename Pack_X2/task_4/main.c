#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t *arr;
int N;

void Init(int64_t *arr, int n);
int Query(int l, int64_t sum);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M, L;
    int64_t S;
    scanf("%d %d", &N, &M);

    arr = (int64_t *) malloc(N * sizeof(int64_t));

    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    Init(arr, N);

    while (M--) {
        scanf("%d %lld", &L, &S);

        printf("%d\n", Query(L, S));
    }

    free(arr);

    return 0;
}