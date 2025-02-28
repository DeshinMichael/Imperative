#include <stdio.h>
#include <assert.h>
#include "modular.h"

int MOD = 7;

long long power(long long num, long long p) {
    long long res = 1;
    num %= MOD;
    while (p != 0) {
        if (p % 2) {
            res = (res * num) % MOD;
        }
        num = (num * num) % MOD;
        p /= 2;
    }
    return (int)res;
}

int pnorm(int num) {
    return (num % MOD + MOD) % MOD;
}

int padd(int num1, int num2) {
    assert(num1 >= 0 && num1 < MOD);
    assert(num2 >= 0 && num2 < MOD);

    return pnorm(num1 + num2);
}

int psub(int num1, int num2) {
    assert(num1 >= 0 && num1 < MOD);
    assert(num2 >= 0 && num2 < MOD);

    return pnorm(num1 - num2);
}

int pmul(int num1, int num2) {
    assert(num1 >= 0 && num1 < MOD);
    assert(num2 >= 0 && num2 < MOD);

    long long res = ((long long)num1 * num2) % MOD;
    return (int)res; 
}

int pdiv(int num1, int num2) {
    assert(num1 >= 0 && num1 < MOD);
    assert(num2 >= 0 && num2 < MOD);

    assert(num2 != 0);

    long long inv_num2 = power(num2, MOD-2);
    long long res = ((long long)num1 * inv_num2) % MOD;
    return (int)res;
}