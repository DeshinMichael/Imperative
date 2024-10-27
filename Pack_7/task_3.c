#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    char bits[n];
    scanf("%s", bits);

    int num = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i / 8 + 1 == (n - 1) / 8 + 1) {
            if (bits[i] == '1') {
                num += 1U << (i % 8);
            }
            if (i == n - 1) {
                printf("%d ", num);
            }
        } else {
            if (bits[i] == '1') {
                num += 1U << (i % 8);
            }
            count++;
            if (count == 8) {
                printf("%d ", num);
                count = 0;
                num = 0;
            }
        }
    }

    return 0;
}