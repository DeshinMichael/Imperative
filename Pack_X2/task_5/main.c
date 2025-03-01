#include <stdio.h>

typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M, X;
    scanf("%d", &M);

    Factors factor;

    while (M--) {
        scanf("%d", &X);

        Factorize(X, &factor);

        printf("%d = ", X);

        if (factor.k == 0) {
            printf("1\n");
        } else {
            printf("%d^%d", factor.primes[0], factor.powers[0]);
            for (int i = 1; i < factor.k; i++) {
                printf(" * %d^%d", factor.primes[i], factor.powers[i]);
            }
            printf("\n");
        }
    }

    return 0;
}