#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Pair_t {
    uint32_t key;
    uint32_t value;
} Pair;

int radix_sort(Pair *a, int n) {
    Pair *b = (Pair *) malloc(n * sizeof(Pair));

    for (int byte = 0; byte <= 3; byte++) {
        int count[256] = {0};

        for (int i = 0; i < n; i++) {
            uint32_t curr_byte = (a[i].key >> (byte * 8)) & 0xFF;
            count[curr_byte]++;
        }

        for (int i = 1; i < 256; i++) {
            count[i] += count[i-1];
        }

        for (int i = n-1; i >= 0; i--) {
            uint32_t curr_byte = (a[i].key >> (byte * 8)) & 0xFF;
            b[--count[curr_byte]] = a[i];
        }

        for (int i = 0; i < n; i++) {
            a[i] = b[i];
        }
    }

    free(b);
}

int main() {

    FILE* input = fopen("input.txt", "rb");

    int n;
    fread(&n, sizeof(int), 1, input);

    Pair *pairs = (Pair *) malloc(n * sizeof(Pair));

    fread(pairs, sizeof(Pair), n, input);

    radix_sort(pairs, n);

    FILE* output = fopen("output.txt", "wb");

    fwrite(pairs, sizeof(Pair), n, output);

    free(pairs);

    fclose(input);
    fclose(output);

    return 0;
}