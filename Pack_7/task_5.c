#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    int n, count = 0;
    scanf("%d", &n);

    uint64_t *masks = (uint64_t *) malloc(n * sizeof(uint64_t));

    for (int i = 0; i < n; i++) {
        scanf("%llx", &masks[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!(masks[i] & masks[j])) {
                count++;
            } 
        }
    }

    printf("%d", count);

    free(masks);

    return 0;
}