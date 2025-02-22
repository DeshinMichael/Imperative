#include <stdio.h>
#include <stdlib.h>

#define P 1000000007

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

void swap(ll **matrix, int i, int j) {
    ll *temp = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = temp;
}

int straight_motion(ll **matrix, int k, int n, ll p, int *free_vars) {
    int pivot_row, rank = 0;
    ll t, inv;

    for (int c1 = 0, c2 = 0; c1 < k && c2 < n; c1++, c2++) {
        pivot_row = -1;

        for (int i = c1; i < k; i++) {
            if (matrix[i][c2] != 0) {
                pivot_row = i;
                break;
            }
        }

        if (pivot_row == -1) {
            free_vars[c2] = 1;
            c1--;
            continue;
        }

        swap(matrix, c1, pivot_row);

        inv = power(matrix[c1][c2], p-2, p);
        for (int i = c1+1; i < k; i++) {
            t = (matrix[i][c2] * inv) % p;

            for (int j = c2; j < n+1; j++) {
                matrix[i][j] = (matrix[i][j] - (matrix[c1][j] * t) % p + p) % p;
            }
        }

        rank++;
    }

    for (int i = rank; i < k; i++) {
        if (matrix[i][n] != 0) {
            return -1;
        }
    }

    return rank;
}

void reverse_motion(ll **matrix, ll *X, int rank, int n, ll p, int *free_vars) {
    ll sum, inv;
    int pivot_col;

    for (int i = rank-1; i >= 0; i--) {
        sum = 0;
        pivot_col = -1;

        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                pivot_col = j;
                break;
            }
        }

        for (int j = pivot_col+1; j < n; j++) {
            sum = (sum + (matrix[i][j] * X[j]) % p) % p;
        }

        if (pivot_col == -1) continue;

        inv = power(matrix[i][pivot_col], p-2, p);
        X[pivot_col] = ((matrix[i][n] - sum) % p + p) % p;
        X[pivot_col] = (X[pivot_col] * inv) % p;
    }

    for (int i = 0; i < n; i++) {
        if (free_vars[i]) {
            X[i] = -1;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, k;
    ll p;
    scanf("%d %d %lld", &n, &k, &p);

    ll **A = (ll **) malloc(k * sizeof(ll *));
    for (int i = 0; i < k; i++) {
        A[i] = (ll *) malloc((n+1) * sizeof(ll));
        for (int j = 0; j < n+1; j++) {
            scanf("%lld", &A[i][j]);
        }
    }
    ll *X = (ll *) malloc(n * sizeof(ll));
    int *free_vars = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        X[i] = 0;
        free_vars[i] = 0;
    }

    int rank = straight_motion(A, k, n, p, free_vars);

    if (rank == -1) {
        printf("0");
    } else {
        int k_free_vars = n - rank;
        ll num_res = power(p, k_free_vars, P);

        reverse_motion(A, X, rank, n, p, free_vars);

        if (k_free_vars == 0) {
            printf("1\n");
            for (int i = 0; i < n; i++) {
                printf("%lld\n", X[i]);
            }
        } else {
            printf("%lld", num_res % P);
        }
    }

    for (int i = 0; i < k; i++) {
        free(A[i]);
    }
    free(A);
    free(X);
    free(free_vars);

    return 0;
}