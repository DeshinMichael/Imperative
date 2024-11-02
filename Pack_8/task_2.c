#include <stdio.h>
#include <stdint.h>

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    double x;
    int p, q;
    uint64_t m;
    for (int i = 0; i < n; i++) {
        scanf("%d/%d xor %llx", &p, &q, &m);
        x = (double) p / q;
        uint64_t *x_bits = (uint64_t*)&x;
        *x_bits ^= m;
        printf("%0.15g\n", x);
    }

    return 0;
}