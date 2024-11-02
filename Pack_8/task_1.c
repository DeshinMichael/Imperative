#include <stdio.h>
#include <stdint.h>

uint32_t swap_endian(uint32_t num) {
    return ((num & 0xFF000000) >> 24) | 
           ((num & 0x00FF0000) >> 8)  | 
           ((num & 0x0000FF00) << 8)  | 
           ((num & 0x000000FF) << 24);
}

int main() {
    FILE* input = fopen("1.in", "rb");

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, input);

    int is_l_endian = (n & 0xFF000000) == 0;
    if (!is_l_endian) {
        n = swap_endian(n);
    }

    int32_t num[10000];
    fread(num, sizeof(int32_t), n, input);
    fclose(input);

    int32_t sum = 0;
    for (size_t i = 0; i < n; i++) {
        if (!is_l_endian) {
            num[i] = swap_endian(num[i]);
        }
        sum += num[i];
    }

    FILE* output = fopen("1.out", "wb");

    if (!is_l_endian) {
        sum = swap_endian((uint32_t) sum);
    }

    fwrite(&sum, sizeof(int32_t), 1, output);
    fclose(output);

    return 0;
}