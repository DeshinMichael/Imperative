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
                scanf("%d %d", &left, &right);
                if (bitsetAny(words, left, right) == 0) {
                    printf("none\n");
                } else {
                    printf("some\n");
                }
                break;
        }
    }

    free(words);

    return 0;
}