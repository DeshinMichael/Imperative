#include "myblas.h"

void dgemm(
    int m, int n, int k,
    double alpha, const double *A, const double *B,
    double beta, double *C
    ) {
        double sum;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum = 0.0;

                for (int h = 0; h < k; h++) {
                    sum += A[i * k + h] * B[h * n + j];
                }
                C[i * n + j] = alpha * sum + beta * C[i * n + j];
            }
        }
    }