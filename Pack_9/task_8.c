#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);

    int l, r, k;
    scanf("%d %d %d", &l, &r, &k);

    int count = 0;
    for (int i = l; i <= r-k+1; i++) {
        for (int j = (r-i)/k+1; j*(k-1) <= (r-i); j++) {
            count++;
        }
    }

    printf("%d", count);

    return 0;
}