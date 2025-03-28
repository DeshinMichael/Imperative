#pragma once

typedef struct IntegerSet_t {
    int *set;
    int n;
} IntegerSet;

IntegerSet *CreateSet(int *set, int n);
void DeleteSet(IntegerSet *int_set);
int IsInSet(IntegerSet *int_set, int a);