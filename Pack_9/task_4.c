#include <stdio.h>
#include <stdlib.h>

void merge(const int *a, int ak, const int *b, int bk, int *res) {
    int ai = 0;
    int bi = 0;
    int resi = 0;
    while (ai < ak && bi < bk) {
        if (a[ai] < b[bi]) {
            res[resi] = a[ai];
            ai++;
            resi++;
        } else {
            res[resi] = b[bi];
            bi++;
            resi++;
        }
    }

    while (ai < ak) {
        res[resi] = a[ai];
        ai++;
        resi++;
    }

    while (bi < bk) {
        res[resi] = b[bi];
        bi++;
        resi++;
    }
}

void mergeSort(int *a, int n) {
    if (n <= 1) return;

    int mid = n / 2;
    int *left = (int *) malloc(mid * sizeof(int));
    int *right = (int *) malloc((n-mid) * sizeof(int));

    for (int i = 0; i < mid; i++) {
        left[i] = a[i];
    }

    for (int i = mid; i < n; i++) {
        right[i-mid] = a[i];
    }

    mergeSort(left, mid);
    mergeSort(right, n-mid);

    merge(left, mid, right, n-mid, a);

    free(left);
    free(right);
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, input);

    int *a = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fread(&a[i], sizeof(int), 1, input);
    }

    mergeSort(a, n);

    for (int i = 0; i < n; i++) {
        fwrite(&a[i], sizeof(int), 1, output);
    }

    fclose(input);
    fclose(output);

    free(a);

    return 0;
}