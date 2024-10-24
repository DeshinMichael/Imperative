#include <stdio.h>

#define MAX_N 1000

double binom[MAX_N + 1][MAX_N + 1]; // массив для хранения

// создание треугольника Паскаля
void create_binomial() {
    for (int n = 0; n <= MAX_N; n++) {
        binom[n][0] = 1.0;
        for (int k = 1; k <= n; k++) {
            binom[n][k] = binom[n - 1][k - 1] + binom[n - 1][k];
        }
    }
}

int main() {
    int Q, n, k;
    scanf("%d", &Q);

    create_binomial();

    // ввод и вывод
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &n, &k);
        printf("%0.10g\n", binom[n][k]);
    }

    return 0;
}   