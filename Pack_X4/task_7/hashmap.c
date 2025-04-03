#include "hashmap.h"
#include <stdlib.h>

#define INIT_CAP 4
#define LOAD_FACT 0.77

static const int CELL_EMPTY = 0;
static const int CELL_OCCUPIED = 1;
static const int CELL_TOMBSTONE = 2;

static void HM_InitStorage(HashMap *self, int capacity) {
    self->table = (Cell *) calloc(capacity, sizeof(Cell));
    self->capacity = capacity;
    self->count = 0;
}

static int probe_index(const HashMap *self, cpvoid key, int *found_exist_key) {
    uint32_t hash = self->hash(self->context, key);
    int index = hash % self->capacity;

    int first_tomb_index = -1;

    for (int i = 0; i < self->capacity; i++) {
        int probe = (index + i) % self->capacity;
        int st = self->table[probe].state;

        if (st == CELL_EMPTY) {
            return (first_tomb_index != -1) ? first_tomb_index : probe;
        } else if (st == CELL_TOMBSTONE) {
            if (first_tomb_index == -1) first_tomb_index = probe;
        } else {
            if (self->equals(self->context, self->table[probe].key, key)) {
                *found_exist_key = probe;
                return probe;
            }
        }
    }
}

static void HM_Rehash(HashMap *self) {
    int old_capacity = self->capacity;
    Cell *old_table = self->table;

    int new_capacity = (old_capacity == 0) ? INIT_CAP : old_capacity * 2;
    HM_InitStorage(self, new_capacity);

    for (int i = 0; i < old_capacity; i++) {
        if (old_table[i].state == CELL_OCCUPIED) {
            HM_Set(self, old_table[i].key, old_table[i].value);
        }
    }

    free(old_table);
}

static void HM_EnsureCapacity(HashMap *self) {
    if (!self->capacity) {
        HM_InitStorage(self, INIT_CAP);
        return;
    }

    double load_fact = (double)self->count / self->capacity;
    if (load_fact > LOAD_FACT)  {
        HM_Rehash(self);
    }
}

HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context) {
    HashMap hash_map;
    HM_InitStorage(&hash_map, INIT_CAP);
    hash_map.equals = ef;
    hash_map.hash = hf;
    hash_map.context = context;
    return hash_map;
}

void HM_Clear(HashMap *self) {
    if (!self) return;
    if (self->table) free(self->table);
    self->table = NULL;
    self->count = 0;
    self->capacity = 0;
}

cpvoid HM_Get(const HashMap *self, cpvoid key) {
    if (!self->table || self->capacity == 0) {
        return NULL;
    }

    int found_exist_key = -1;
    int probe = probe_index(self, key, &found_exist_key);
    if (found_exist_key >= 0) {
        return self->table[found_exist_key].value;
    }
    return NULL;
}

void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    HM_EnsureCapacity(self);

    int found_exist_key = -1;
    int probe = probe_index(self, key, &found_exist_key);

    if (probe < 0) {
        HM_Rehash(self);
        probe = probe_index(self, key, &found_exist_key);
    }

    if (found_exist_key >= 0) {
        self->table[found_exist_key].value = value;
        return;
    }
    
    if (self->table[probe].state != CELL_OCCUPIED) {
        self->count++;
    }
    self->table[probe].key = key;
    self->table[probe].value = value;
    self->table[probe].state = CELL_OCCUPIED;
}

cpvoid HM_Remove(HashMap *self, cpvoid key) {
    if (!self->table || self->capacity == 0) {
        return NULL;
    }

    int found_exist_key = -1;
    int probe = probe_index(self, key, &found_exist_key);

    if (found_exist_key < 0) {
        return NULL;
    }

    cpvoid old_value = self->table[found_exist_key].value;
    self->table[found_exist_key].state = CELL_TOMBSTONE;
    self->table[found_exist_key].key = NULL;
    self->table[found_exist_key].value = NULL;
    self->count--;
    return old_value;
}