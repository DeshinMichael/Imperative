#include <stdio.h>

#define L 301

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);

    int ans[5] = {1, 1, 1, 1, 1};

    int mas12[L] = {0}, mas34[L] = {0};

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);

        if (mas12[x] != 0 && mas12[x] != y) {
            ans[0] = 0;
        }

        if (mas34[y] != 0 && mas34[y] != x) {
            ans[2] = 0;
        }

        mas12[x] = y;
        mas34[y] = x;
    }

    for (int i = 1; i <= n; i++) {
        if (mas12[i] == 0) {
            ans[1] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (mas34[i] == 0) {
            ans[3] = 0;
        }
    }

    if (ans[0] != 1 || ans[2] != 1 || ans[3] != 1)
        ans[4] = 0;


    if (ans[0] == 0)
        printf("0");
    else {
        for (int i = 0; i < 5; i++) {
            if (ans[i] != 0)
                printf("%d ", i+1);
        }
    }
}