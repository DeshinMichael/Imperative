#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TABLE_SIZE 1000000

typedef struct HashNode_t {
    int num;
    uint64_t key;
    struct HashNode_t *next;
} HashNode;

typedef struct HashTable_t {
    HashNode **buckets;
    uint64_t size;
} HashTable;

uint64_t jenkins_hash(const uint8_t* key, size_t len) {
    uint64_t hash = 0;
    for (size_t i = 0; i < len; i++) {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

uint64_t func(uint64_t s, int a, int b, int c, uint64_t M) {
    return (s*s*a + s*b + c) % M;
}

HashTable *createHashTable(uint64_t size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = calloc(size, sizeof(HashNode *));
    return table;
}

HashNode *createNode(const uint64_t key, const int num) {
    HashNode *node = malloc(sizeof(HashNode));
    node->num = num;
    node->key = key;
    node->next = NULL;
    return node;
}

int valueExists(HashTable *table, uint64_t key, int *found_num) {
    uint64_t index = jenkins_hash((uint8_t *)&key, sizeof(key)) % table->size;
    HashNode *current = table->buckets[index];
    while (current) {
        if (current->key == key) {
            if (found_num) {
                *found_num = current->num;
            }
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void insert(HashTable *table, const uint64_t key, const int num) {
    uint64_t index = jenkins_hash((uint8_t *)&key, sizeof(key)) % table->size;
    HashNode *node = createNode(key, num);
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

void freeHashTable(HashTable *table) {
    for (uint64_t i = 0; i < table->size; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    freopen("input.txt", "r", stdin);

    uint64_t M;
    int a, b, c;
    scanf("%llu", &M);
    scanf("%d %d %d", &a, &b, &c);

    HashTable *table = createHashTable(TABLE_SIZE);

    uint64_t state = 1;
    int num = 0;
    insert(table, state, num);

    int found_num;
    while (num <= 2000000) {
        num++;
        state = func(state, a, b, c, M);

        if (!valueExists(table, state, &found_num)) {
            insert(table, state, num);
        } else {
            printf("%d %d", found_num, num);
            break;
        }
    }

    freeHashTable(table);

    return 0;
}