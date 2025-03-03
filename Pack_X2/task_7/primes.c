#include "primes.h"

#define MAX_N 10000000

static char sieve[MAX_N+1] = {0};
static char init = 0;
static int prime_count[MAX_N+1] = {0};

static void init_sieve() {
    if (init) return;
    init = 1;

    for (int i = 2; i <= MAX_N; i++) {
        sieve[i] = 1;
    }

    for (int i = 2; i*i <= MAX_N; i++) {
        if (sieve[i]) {
            for (int j = i*i; j <= MAX_N; j += i) {
                sieve[j] = 0;
            }
        }
    }

    for (int i = 1; i <= MAX_N; i++) {
        prime_count[i] = prime_count[i-1] + (sieve[i] ? 1 : 0);
    }
}

int isPrime(int x) {
    if (!init) init_sieve();

    if (x < 2) return 0;
    return sieve[x];
}

int findNextPrime(int x) {
    if (!init) init_sieve();
    
    for (int i = x; i <= MAX_N; i++) {
        if (sieve[i]) return i;
    }
    return 10000019;
}

int getPrimesCount(int l, int r) {
    if (!init) init_sieve();
    
    return (l == 0) ? prime_count[r-1] : (prime_count[r-1] - prime_count[l-1]);
}