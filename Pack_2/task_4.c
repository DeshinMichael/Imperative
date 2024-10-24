#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    int max_sum = -100000;
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum > max_sum) {
                max_sum = sum;
                l = i;
                r = j;
            }
        }
    }
    printf("%d %d %d", l, r, max_sum);

    return 0;
}