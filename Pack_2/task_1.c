#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i; j < n; j++) {
            if (b[i] > b[j])
                count++;
        }
        printf("%d ", count);
    }

    return 0;
}