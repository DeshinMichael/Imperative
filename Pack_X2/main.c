#include "modular.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

int main() {
    MOD = 13;
    assert(pnorm(45) == 6);
    assert(pnorm(-6) == 7);
    assert(pnorm(13) == 0);
    assert(padd(7, 7) == 1);
    assert(padd(11, 2) == 0);
    assert(psub(2, 3) == 12);
    assert(psub(7, 7) == 0);
    assert(pmul(7, 6) == 3);
    assert(pmul(4, 4) == 3);

    int a1 = pnorm(1000000000);
    int b1 = pnorm(999999994);
    assert(a1 == 12);
    assert(b1 == 6);
    assert(pmul(a1, b1) == 7);

    int x = pmul(padd(7, psub(2, 3)), 5);
    assert(x == 4);
    int y = pdiv(7, x);
    assert(pmul(x, y) == 7);

    MOD = 2;
    assert(pnorm(5) == 1);
    assert(padd(1, 1) == 0);
    assert(psub(1, 1) == 0);
    assert(pmul(1, 1) == 1);
    assert(pmul(1, 0) == 0);
    assert(pdiv(1, 1) == 1);

    MOD = 999999929;
    assert(pnorm(2000000000) == 142);
    assert(padd(77, 1) == 78);
    assert(psub(10, 20) == 999999919);
    assert(pdiv(5, 1) == 5);

    int a2 = pnorm(999999920);
    int b2 = pnorm(987654321);
    assert(a2 == 999999920);
    assert(b2 == 987654321);
    assert(pmul(a2, b2) == 111110472);

    MOD = 182616307;
    int z = pdiv(23905215, 94958545);
    assert(z >= 0 && z < 182616307);

    printf("All tests accepted");

    return 0;
}