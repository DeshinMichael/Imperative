#include <stddef.h>

#define CblasRowMajor 101
#define CblasNoTrans 111

void cblas_dgemm(const int Order, const int TransA, const int TransB,
    const int M, const int N, const int K,
    const double alpha, const double *A, const int lda,
    const double *B, const int ldb, const double beta, double *C, 
    const int ldc) {

    if (Order != CblasRowMajor || TransA != CblasNoTrans || TransB != CblasNoTrans) {
        return;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < K; k++) {
            sum += A[i * lda + k] * B[k * ldb + j];
            }
            C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
        }
    }
}