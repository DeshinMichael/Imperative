#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct DescBits_t {
    uint32_t L;
    uint64_t bits;
} DescBits;

int main() {

    FILE* input = fopen("input.txt", "rb");

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, input);

    DescBits descs[n];
    uint8_t bit;
    for (int i = 0; i < n; i++) {
        fread(&descs[i].L, sizeof(uint32_t), 1, input);
        descs[i].bits = 0;
        for (int j = 0; j < descs[i].L; j++) {
            fread(&bit, sizeof(uint8_t), 1, input);
            descs[i].bits = descs[i].bits + ((uint64_t) bit << j);
        }
    }

    uint32_t m;
    fread(&m, sizeof(uint32_t), 1, input);

    FILE* output = fopen("output.txt", "wb");

    uint16_t symbol;
    uint8_t curr_byte = 0;
    uint64_t curr_desc;
    int count = 0;
    for (int i = 0; i < m; i++) {
        fread(&symbol, sizeof(uint16_t), 1, input);
        curr_desc = descs[symbol].bits;
        for (int j = 0; j < descs[symbol].L; j++) {
            bit = (curr_desc >> j) & 1;
            curr_byte = curr_byte + (bit << count);
            count++;
            if (count == 8) {
                fwrite(&curr_byte, sizeof(int8_t), 1, output);
                curr_byte = 0;
                count = 0;
            }
        }
    }

    if (count > 0) {
        fwrite(&curr_byte, sizeof(int8_t), 1, output);
    }

    fclose(input);
    fclose(input);

    return 0;
}