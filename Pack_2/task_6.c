#include <stdio.h>

int main() {

    int exists_in_b[100001] = {0};

    int n, s;
    scanf("%d", &n);
    int a[n];
    int max_v = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {   
        scanf("%d", &s);
        if (exists_in_b[s] == 0)
            k++;
        exists_in_b[s] = 1;
        if (s > max_v)
            max_v = s;
    }

    int m;
    scanf("%d", &m);
    int b[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &s);
        if (exists_in_b[s] == 1)
            k--;
        exists_in_b[s] = 0;
    }
    
    printf("%d\n", k);
    for (int i = 0; i <= max_v; i++) {
        if (exists_in_b[i] == 1) {
            printf("%d ", i);
        }
    }
    
    return 0;
}