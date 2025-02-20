#include <stdio.h>

#define M 1000000007
#define MAX_N 1000001

typedef long long ll;

ll fact[MAX_N+1];

ll power(ll num, int p) {
    ll res = 1;
    while (p != 0) {
        if (p % 2) {
            res = (res * num) % M;
        }
        num = (num * num) % M;
        p /= 2;
    }
    return res;
}

void init_fact_tables() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        fact[i] = (fact[i-1] * i) % M;
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int t, n, k;
    scanf("%d", &t);

    init_fact_tables();

    while (t--) {
        scanf("%d %d", &n, &k);

        if (k < 0 || k > n) {
            printf("0\n");
            continue;
        }

        ll res = fact[n];
        res = (res * power((fact[k] * fact[n-k]) % M, M-2)) % M;

        printf("%lld\n", res);
    }

    return 0;
}