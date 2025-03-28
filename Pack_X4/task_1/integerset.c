#include "integerset.h"
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

IntegerSet *CreateSet(int *set, int n) {
    if (n == 0) {
        IntegerSet *int_set = (IntegerSet *) malloc(sizeof(IntegerSet));
        int_set->set = NULL;
        int_set->n = 0;
        return int_set;
    }

    if (set == NULL) return NULL;

    IntegerSet *int_set = (IntegerSet *) malloc(sizeof(IntegerSet));
    int_set->set = (int *) malloc(n * sizeof(int));
    int_set->n = n;

    for (int i = 0; i < n; i++) {
        int_set->set[i] = set[i];
    }

    qsort(int_set->set, n, sizeof(int), cmp_int);

    for (int i = 1; i < n; i++) {
        if (int_set->set[i] == int_set->set[i-1]) {
            free(int_set->set);
            free(int_set);
            return NULL;
        }
    }

    return int_set;
}

void DeleteSet(IntegerSet *int_set) {
    if (!int_set) return;
    free(int_set->set);
    free(int_set);
}

int IsInSet(IntegerSet *int_set, int a) {
    if (!int_set) return 0;
    return bsearch(&a, int_set->set, int_set->n, sizeof(int), cmp_int) != NULL;
}