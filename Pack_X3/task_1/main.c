#include <stdio.h>
#include "myblas.h"

int main() {
    const double X[] = {1.0, 2.0, 3.0};
    double Y[] = {7.0, 7.0, 7.0};

    dcopy(3, X, Y);
    for (int i = 0; i < 3; i++) {
        printf("%lf\n", Y[i]);
    }

    return 0;
}