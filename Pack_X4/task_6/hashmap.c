#include "hashmap.h"
#include <stdlib.h>

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap hash_map;
    hash_map.table = (Cell *) calloc(size, sizeof(Cell));
    hash_map.size = size;
    hash_map.equals = ef;
    hash_map.hash = hf;
    return hash_map;
}

void HM_Destroy(HashMap *self) {
    if (!self) return;
    free(self->table);
    self->table = NULL;
    self->equals = NULL;
    self->hash = NULL;
    self->size = 0;
}

cpvoid HM_Get(const HashMap *self, cpvoid key) {
    uint32_t hash = self->hash(key);
    int index = hash % self->size;
    for (int i = 0; i < self->size; i++) {
        int probe = (index + i) % self->size;
        if (!self->table[probe].is_occupied)
            return NULL;
        if (self->equals(self->table[probe].key, key))
            return self->table[probe].value;
    }
    return NULL;
}

void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    uint32_t hash = self->hash(key);
    int index = hash % self->size;
    for (int i = 0; i < self->size; i++) {
        int probe = (index + i) % self->size;
        if (!self->table[probe].is_occupied || self->equals(self->table[probe].key, key)) {
            self->table[probe].key = key;
            self->table[probe].value = value;
            self->table[probe].is_occupied = 1;
            return;
        }
    }
}