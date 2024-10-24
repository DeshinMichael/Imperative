#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int res[10001] = {0};
    int max = 0;
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        res[c]++;
        if (c > max)
            max = c;
    }
    for (int i = 1; i < max+1; i++) {
        if (res[i] > 0)
            printf("%d: %d\n", i, res[i]);
    }

    return 0;
}