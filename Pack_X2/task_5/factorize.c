typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void init_factor(Factors *factor) {
    factor->k = 0;
    for (int i = 0; i < 32; i++) {
        factor->primes[i] = 0;
        factor->powers[i] = 0;
    }
}

void Factorize(int X, Factors *res) {
    init_factor(res);

    if (X % 2 == 0) {
        res->primes[res->k] = 2;
        while (X % 2 == 0) {
            X /= 2;
            res->powers[res->k]++;
        }
        res->k++;
    }
    
    for (int i = 3; i*i <= X; i += 2) {
        if (X % i == 0) {
            res->primes[res->k] = i;
            while (X % i == 0) {
                X /= i;
                res->powers[res->k]++;
            }
            res->k++;
        }
    }

    if (X > 1) {
        res->primes[res->k] = X;
        res->powers[res->k] = 1;
        res->k++;
    }
}