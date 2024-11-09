#include <stdio.h>
#include <stdlib.h>

int merge(const int *a, int ak, const int *b, int bk, int *res) {
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

    return ak + bk;
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");

    int n, m;
    fread(&n, sizeof(int), 1, input);
    fread(&m, sizeof(int), 1, input);

    int *a = (int *) malloc(n * sizeof(int));
    int *b = (int *) malloc(m * sizeof(int));
    int *res = (int *) malloc((n+m) * sizeof(int));

    for (int i = 0; i < n; i++) {
        fread(&a[i], sizeof(int), 1, input);
    }

    for (int i = 0; i < m; i++) {
        fread(&b[i], sizeof(int), 1, input);
    }
    
    int len_res = merge(a, n, b, m, res);
    for (int i = 0; i < len_res; i++) {
        fwrite(&res[i], sizeof(int), 1, output);
    }

    fclose(input);
    fclose(output);

    free(a);
    free(b);
    free(res);

    return 0;
}