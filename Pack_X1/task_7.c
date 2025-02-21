#include <stdio.h>
#include <stdlib.h>

void swap(double **matrix, int i, int j) {
    double *temp = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = temp;
}

void straight_motion(double **matrix, int n) {
    int is_null_col = 1;
    double t;
    int q;

    for (int k = 0, q = 0; k < n && q < n; k++, q++) {

        for (int i = q; i < n; i++) {
            if (matrix[i][q] != 0) {
                swap(matrix, q, i);
                is_null_col = 0;
                break;
            }
        }

        if (is_null_col) {
            q--;
            continue;
        }

        for (int i = k+1; i < n; i++) {
            t = matrix[i][k] / matrix[k][k];
            for (int j = k; j < n+1; j++) {
                matrix[i][j] -= matrix[k][j] * t;
            }
        }
    }
}

void reverse_motion(double **matrix, double *X, int n) {
    double sum;
    for (int i = n-1; i >= 0; i--) {
        sum = 0;
        for (int j = i+1; j < n; j++) {
            sum += matrix[i][j] * X[j];
        }

        X[i] = (matrix[i][n] - sum) / matrix[i][i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    double **A = (double **) malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *) malloc((n+1) * sizeof(double));
        for (int j = 0; j < n+1; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    double *X = (double *) malloc(n * sizeof(double));

    straight_motion(A, n);
    reverse_motion(A, X, n);

    for (int i = 0; i < n; i++) {
        printf("%.10f\n", X[i]);
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(X);

    return 0;
}