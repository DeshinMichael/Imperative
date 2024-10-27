#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int n = 0;
    n += 1U << 8;
    printf("%d", n);

    return 0;
}