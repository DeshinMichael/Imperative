#include "myblas.h"

void dgemv(
    int m, int n,
    double alpha, const double *A, const double *X,
    double beta, double *Y) {
        double sum;
        for (int i = 0; i < m; i++) {
            sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += A[i * n + j] * X[j];
            }
            Y[i] = alpha * sum + beta * Y[i];
        }
    }

void dger(
    int m, int n,
    double alpha, const double *X, const double *Y,
    double *A) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] += alpha * X[i] * Y[j];
            }
        }
    }