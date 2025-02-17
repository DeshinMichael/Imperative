#include <stdio.h>

typedef long long ll;

ll power(ll num, ll p, ll m) {
    ll res = 1;
    while (p != 0) {
        if (p % 2) {
            res = (res * num) % m;
        }
        num = (num * num) % m;
        p /= 2;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    ll m, a, b;

    scanf("%d %lld", &t, &m);

    for (int i = 0; i < t; i++) {
        scanf("%lld", &a);

        b = power(a, m-2, m) % m;

        b = a * b % m == 1 ? b : -1;
        printf("%lld\n", b);
    }

    return 0;
}