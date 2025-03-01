#include <stdlib.h>

double Function(double x) {
    if (x < 0.0 || x > 1.0)
        exit(666);
    return x * x - x;
}