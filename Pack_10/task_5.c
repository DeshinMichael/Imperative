#include <stdio.h>
#include <stdlib.h>

double find_taylor_series_sin(double x) {
    double sum = 0.0;
    double term = x;
    int n = 1;

    while (term > 1e-12 || term < -1e-12) {
        sum += term;
        term *= -x * x / (2 * n * (2 * n + 1));
        n++;
    }

    return sum;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    double *arr = (double *) malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%0.15lf\n", find_taylor_series_sin(arr[i]));
    }

    free(arr);

    return 0;
}