#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    long long m;
    scanf("%d %lld", &n, &m);

    long *notes = (long *) malloc(n * sizeof(long)); // для хранения событий

    // ввод событий
    for (int i = 0; i < n; i++) {
        scanf("%ld", &notes[i]);
    }

    int start = 0; // индекс начального события
    for (int i = 0; i < n; i++) {
        while (start < i && notes[i] - notes[start] > m) {
            start++;    
        }
        printf("%d\n", i - start + 1);
    }

    free(notes);

    return 0;
}