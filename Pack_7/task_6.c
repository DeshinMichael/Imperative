#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BITS 20000000
#define BITS_WORD (sizeof(bitword) * 8)

typedef uint64_t bitword;

void bitsetZero(bitword *arr, int num) {
    int num_words = (num + BITS_WORD - 1) / BITS_WORD;
    for (int i = 0; i < num_words; i++) {
        arr[i] = 0;
    }
}

int bitsetGet(const bitword *arr, int idx) {
    int word_idx = idx / BITS_WORD;
    int bit_idx = idx % BITS_WORD;
    return (arr[word_idx] >> bit_idx) & 1;
}

void bitsetSet(bitword *arr, int idx, int newval) {
    int word_idx = idx / BITS_WORD;
    int bit_idx = idx % BITS_WORD;
    if (newval) {
        arr[word_idx] |= (1ULL << bit_idx);
    } else {
        arr[word_idx] &= ~(1ULL << bit_idx);
    }
}

int bitsetAny(const bitword *arr, int left, int right) {

    if (left / BITS_WORD == right / BITS_WORD) {
        for (int i = left % BITS_WORD; i < right % BITS_WORD; i++) {
            if ((arr[left / BITS_WORD] >> i) & 1) return 1;
        }
        return 0;
    }

    for (int i = left % BITS_WORD; i < BITS_WORD; i++) {
        if ((arr[left / BITS_WORD] >> i) & 1) return 1;
    }

    for (int i = left / BITS_WORD + 1; i < right / BITS_WORD; i++) {
        if (arr[i] != 0) {
            return 1;
        }
    }

    for (int i = 0; i < right % BITS_WORD; i++) {
        if ((arr[right / BITS_WORD] >> i) & 1) return 1;
    }

    return 0;
}

void bitsetSetSeg(bitword *arr, int left, int right, int newval) {

    if (left / BITS_WORD == right / BITS_WORD) {
        for (int i = left % BITS_WORD; i < right % BITS_WORD; i++) {
            if (newval) arr[left / BITS_WORD] |= (1ULL << i);
            else arr[left / BITS_WORD] &= ~(1ULL << i);
        }
        return;
    }

    for (int i = left % BITS_WORD; i < BITS_WORD; i++) {
        if (newval) arr[left / BITS_WORD] |= (1ULL << i);
        else arr[left / BITS_WORD] &= ~(1ULL << i);
    }

    for (int i = left / BITS_WORD + 1; i < right / BITS_WORD; i++) {
        if (newval) arr[i] |= ~0ULL;
        else arr[i] &= 0ULL;
    }

    for (int i = 0; i < right % BITS_WORD; i++) {
        if (newval) arr[right / BITS_WORD] |= (1ULL << i);
        else arr[right / BITS_WORD] &= ~(1ULL << i);
    }
}

void initBitsSetTable(uint8_t *table) {
    for (int i = 0; i < 256; i++) {
        table[i] = (i & 1) + table[i >> 1];
    }
}

int bitsetCount(const bitword *arr, int left, int right) {
    static uint8_t BitsSetTableFF[256];
    static int is_init = 0;

    if (!is_init) {
        initBitsSetTable(BitsSetTableFF);
        is_init = 1;
    }

    int count = 0;

    if (left / BITS_WORD == right / BITS_WORD) {
        for (int i = left % BITS_WORD; i < right % BITS_WORD; i++) {
            if ((arr[left / BITS_WORD] >> i) & 1) count++;
        }
        return count;
    }

    for (int i = left % BITS_WORD; i < BITS_WORD; i++) {
        if ((arr[left / BITS_WORD] >> i) & 1) count++;
    }

    for (int i = left / BITS_WORD + 1; i < right / BITS_WORD; i++) {
        count += BitsSetTableFF[arr[i] & 0xFF] +
                BitsSetTableFF[(arr[i] >> 8) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 16) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 24) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 32) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 40) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 48) & 0xFF] +
                BitsSetTableFF[(arr[i] >> 56) & 0xFF];
    }

    for (int i = 0; i < right % BITS_WORD; i++) {
        if ((arr[right / BITS_WORD] >> i) & 1) count++;
    }

    return count;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, t;
    int num, idx, newval, left, right;  
    scanf("%d", &n);

    bitword *words = (bitword *) malloc(((MAX_BITS + BITS_WORD - 1) / BITS_WORD) * sizeof(bitword));

    for (int i = 0; i < n; i++) {
        scanf("%d", &t);

        switch (t) {
            case 0:
                scanf("%d", &num);
                bitsetZero(words, num);
                break;
            case 1:
                scanf("%d", &idx);
                printf("%d\n", bitsetGet(words, idx));
                break;
            case 2:
                scanf("%d %d", &idx, &newval);
                bitsetSet(words, idx, newval);
                break;
            case 3:
                scanf("%d %d %d", &left, &right, &newval);
                bitsetSetSeg(words, left, right, newval);
                break;
            case 4:
                scanf("%d %d", &left, &right);
                printf("%d\n", bitsetCount(words, left, right));
                break;
        }
    }

    free(words);

    return 0;
}