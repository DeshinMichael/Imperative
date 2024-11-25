#include <stdio.h>
#include <stdlib.h>

void find_refl_trans_closure(int **arr, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] |= (arr[i][k] & arr[k][j]); 
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int **table = (int **) malloc(n * sizeof(int *));

    int c;
    for (int i = 0; i < n; i++) {
        scanf("%c", &c);
        table[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%c", &c);
            table[i][j] = c-'0';
        }
        table[i][i] = 1;
    }

    find_refl_trans_closure(table, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", table[i][j]+'0');
        }
        free(table[i]);
        printf("\n");
    }
    free(table);

    return 0;
}