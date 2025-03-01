#include <stdio.h>

#define h 1e-7

double Function(double x);

double derivative(double x) {
    if (x - h < 0) {
        return (Function(x + h) - Function(x)) / h;
    } else if (x + h > 1) {
        return (Function(x) - Function(x - h)) / h;
    } else {
        return (Function(x + h) - Function(x - h)) / (2*h);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    double x;
    while (M--) {
        scanf("%lf", &x);

        printf("%.15f\n", derivative(x));
    }

    return 0;
}