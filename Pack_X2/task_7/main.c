#include <stdio.h>
#include <assert.h>
#include "primes.h"

int main() {
    assert(isPrime(2) == 1);
    assert(isPrime(3) == 1);
    assert(isPrime(4) == 0);
    assert(isPrime(6) == 0);
    assert(isPrime(17) == 1);
    assert(isPrime(18) == 0);
    assert(isPrime(1) == 0);
    assert(isPrime(0) == 0);
    assert(isPrime(10000000) == 0);
    assert(isPrime(9999991) == 1);

    assert(findNextPrime(0) == 2);
    assert(findNextPrime(1) == 2);
    assert(findNextPrime(2) == 2);
    assert(findNextPrime(4) == 5);
    assert(findNextPrime(14) == 17);
    assert(findNextPrime(17) == 17);
    assert(findNextPrime(18) == 19);
    assert(findNextPrime(10000000) == 10000019);

    assert(getPrimesCount(0, 10) == 4);
    assert(getPrimesCount(3, 10) == 3);
    assert(getPrimesCount(8, 11) == 0);
    assert(getPrimesCount(11, 19) == 3);
    assert(getPrimesCount(10, 20) == 4);
    assert(getPrimesCount(0, 100) == 25);
    assert(getPrimesCount(100, 200) == 21);
    assert(getPrimesCount(1000000, 1000100) == 6);
    assert(getPrimesCount(5, 5) == 0);
    assert(getPrimesCount(0, 1000000) == 78498);
    assert(getPrimesCount(0, 10000000) == 664579);

    printf("All tests passed");

    return 0;
}