#include <stdlib.h>
#include <string.h>

#define ARRAY_DEF(TYPE, NAME) \
void NAME##_init(NAME *vec) { \
    vec->n = 0; \
    vec->capacity = 0; \
    vec->arr = NULL; \
} \
void NAME##_destroy(NAME *vec) { \
    free(vec->arr); \
    vec->arr = NULL; \
    vec->n = 0; \
    vec->capacity = 0; \
} \
void NAME##_reserve(vec, new_cap); \
int NAME##_push(NAME *vec, TYPE value) { \
    if (vec->n == vec->capacity) { \
        int new_cap = (vec->capacity == 0 ? 1 : vec->capacity * 2); \
        NAME##_reserve(vec, new_cap); \
    } \
    vec->arr[vec->n] = value; \
    return vec->n++; \
} \
TYPE NAME##_pop(NAME *vec) { \
    vec->n--; \
    return vec->arr[vec->n]; \
} \
void NAME##_reserve(NAME *vec, int capacity) { \
    if (capacity > vec->capacity) { \
        TYPE *new_arr = (TYPE *) malloc(capacity * sizeof(TYPE)); \
        for (int i = 0; i < vec->n; i++) { \
            new_arr[i] = vec->arr[i]; \
        } \
        free(vec->arr); \
        vec->arr = new_arr; \
        vec->capacity = capacity; \
    } \
} \
void NAME##_resize(NAME *vec, int newCnt, TYPE fill) { \
    if (newCnt > vec->n) { \
        NAME##_reserve(vec, newCnt); \
        for (int i = vec->n; i < newCnt; i++) { \
            vec->arr[i] = fill; \
        } \
        vec->n = newCnt; \
    } else { \
        vec->n = newCnt; \
    } \
} \
void NAME##_insert(NAME *vec, int where, TYPE *arr, int num) { \
    if (num == 0) return; \
    int needed = vec->n + num; \
    if (needed > vec->capacity) { \
        int new_cap = (vec->capacity == 0 ? 1 : vec->capacity); \
        while (new_cap < needed) { \
            new_cap *= 2; \
        } \
        NAME##_reserve(vec, new_cap); \
    } \
    memmove(&vec->arr[where + num], &vec->arr[where], (vec->n - where) * sizeof(TYPE)); \
    memcpy(&vec->arr[where], arr, num * sizeof(TYPE)); \
    vec->n += num; \
} \
void NAME##_erase(NAME *vec, int where, int num) { \
    if (num == 0) return; \
    memmove(&vec->arr[where], &vec->arr[where + num], (vec->n - (where + num)) * sizeof(TYPE)); \
    vec->n -= num; \
} \

#define _ARRAY_DEF(TYPE, NAME) ARRAY_DEF(TYPE, NAME)

_ARRAY_DEF(TYPE, NAME)

#undef TYPE
#undef NAME