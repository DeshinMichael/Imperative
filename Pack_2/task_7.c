#include <stdio.h>

#define L 10001

void insert_sorted(int *a, int s, int el) {
    int j = s-1;

    while (j >= 0 && a[j] >= el) {
        a[j+1] = a[j];
        j--;
    }
    a[j+1] = el;
}

int main() {
    int n, s;
    scanf("%d", &n);
    int a[L];

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        insert_sorted(a, i, a[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    
    return 0;
}