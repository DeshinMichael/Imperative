#pragma once

#include <stdint.h>

#ifdef HASHMAP_EXPORTS
    #define HASHMAP_API __attribute__((visibility("default")))
#else
    #define HASHMAP_API
#endif

//pointer to key or value (untyped)
typedef const void *cpvoid;
//returns 1 if and only if two keys pointed by [a] and [b] are equal
//returns 0 otherwise
typedef int (*EqualFunc)(void *context, cpvoid a, cpvoid b);
//returns 32-bit hash of a key pointed by [key]
typedef uint32_t (*HashFunc)(void *context, cpvoid key);

typedef struct {
    cpvoid key;
    cpvoid value;
    int state;
} Cell;

typedef struct {
    Cell *table;
    int count;
    int capacity;
    EqualFunc equals;
    HashFunc hash;
    void *context;
} HashMap;

//creates and returns new hash table with:
// [ef]–- function which compares keys for equality
// [hf]–- function which produces a hash for a key
// [context]–- a pointer which is passed to HashFunc and EqualFunc
HASHMAP_API HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context);

//frees memory of hash map [self] and resets it to empty state
//it is allowed to use any operations on the table afterwards
HASHMAP_API void HM_Clear(HashMap *self);

//returns value corresponding to the specified key [key] in hash map [self]
//if [key] is not present in the map, then returns NULL
HASHMAP_API cpvoid HM_Get(const HashMap *self, cpvoid key);

//sets value [value] for the key [key] in hash map [self]
//if [self] already has some value for [key], it is overwritten
HASHMAP_API void HM_Set(HashMap *self, cpvoid key, cpvoid value);

//removes key [key] from the table [self]
//returns the value corresponding to key [key] before removal
//if key [key] is not present, then nothing is done, and NULL is returned
HASHMAP_API cpvoid HM_Remove(HashMap *self, cpvoid key);