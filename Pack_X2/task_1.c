#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll extended_gcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    ll gcd = extended_gcd(a, m, &x, &y);

    x = (x % m + m) % m;

    return x;
}

ll chinese_theorem(ll A[], ll M[], int k) {
    ll X = 0, P = 1;

    for (int i = 0; i < k; i++) {
        P *= M[i];
    }

    for (int i = 0; i < k; i++) {
        ll Bi = P / M[i];
        ll invBi = mod_inv(Bi, M[i]);
        
        ll tmp = (A[i] * invBi) % M[i];
        tmp = (tmp * Bi);

        X = (X + tmp) % P;
    }

    return X;
}

int main() {

    freopen("input.txt", "r", stdin);

    int k;
    scanf("%d", &k);

    ll *M = (ll *) malloc(k * sizeof(ll));
    ll *A = (ll *) malloc(k * sizeof(ll));

    for (int i = 0; i < k; i++) {
        scanf("%lld", &M[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%lld", &A[i]);
    }

    ll result = chinese_theorem(A, M, k);

    printf("%lld\n", result);

    free(M);
    free(A);

    return 0;
}