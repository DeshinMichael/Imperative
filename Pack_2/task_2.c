#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = i-1; j < n; j += i) {
            sum += a[j];
        }
        printf("%d\n", sum);
    }

    return 0;
}