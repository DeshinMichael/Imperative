#include <stdio.h>
#include <stdlib.h>

void Rec(int row, char **field, int M, int N, int *cols, int *diag_up, int *diag_dn, int *found) {
    if (row == M) {
        *found = 1;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (field[i][j] == '?')
                    field[i][j] = '.';
        printf("YES\n");
        for (int i = 0; i < M; i++) {
            printf("%s\n", field[i]);
        }
        return;
    }

    for (int col = 0; col < N; col++) {
        if (field[row][col] == '?' && !cols[col] &&
            !diag_dn[row - col + N] && !diag_up[row + col]) {
            field[row][col] = 'X';
            cols[col] = 1;
            diag_dn[row - col + N] = 1;
            diag_up[row + col] = 1;
            
            Rec(row+1, field, M, N, cols, diag_up, diag_dn, found);

            if (*found) return;

            field[row][col] = '?';
            cols[col] = 0;
            diag_dn[row - col + N] = 0;
            diag_up[row + col] = 0;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int M, N;
    scanf("%d %d", &M, &N);

    char **field = (char **) malloc(M * sizeof(char *));
    int *cols = (int *) calloc(N, sizeof(int));
    int *diag_up = (int *) calloc(M+N+1, sizeof(int));
    int *diag_dn = (int *) calloc(M+N+1, sizeof(int));

    for (int i = 0; i < M; i++) {
        field[i] = (char *) malloc((N+1) * sizeof(char));
        scanf("%s", field[i]);
    }

    int found = 0;
    Rec(0, field, M, N, cols, diag_up, diag_dn, &found);

    if (!found) printf("NO");

    for (int i = 0; i < M; i++) {
        free(field[i]);
    }
    free(field);
    free(cols);
    free(diag_up);
    free(diag_dn);

    return 0;
}