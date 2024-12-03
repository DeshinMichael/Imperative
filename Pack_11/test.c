#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define P 1000000007

typedef struct HashNode_t {
    int key;
    struct HashNode_t *next;
} HashNode;

typedef struct HashTable_t {
    HashNode **buckets;
    int size;
} HashTable;

uint32_t jenkins_hash(const uint8_t* key, size_t len) {
    uint32_t hash = 0;
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

HashTable *createHashTable(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = calloc(size, sizeof(HashNode *));
    return table;
}

HashNode *createNode(const int key) {
    HashNode *node = malloc(sizeof(HashNode));
    node->key = key;
    node->next = NULL;
    return node;
}

int valueExists(HashTable *table, int key) {
    uint32_t index = jenkins_hash((uint8_t *)&key, sizeof(key)) % table->size;
    HashNode *current = table->buckets[index];
    while (current) {
        if (current->key == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void insert(HashTable *table, const int key) {
    if (valueExists(table, key)) return;
    uint32_t index = jenkins_hash((uint8_t *)&key, sizeof(key)) % table->size;
    HashNode *node = createNode(key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

void freeHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
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

    int n;
    scanf("%d", &n);

    HashTable *table = createHashTable(n);
    int *res = (int *) malloc(n * sizeof(int));
    int res_size = 0;

    int key;
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        if (!valueExists(table, key)) {
            insert(table, key);
            res[res_size++] = key;
        }
    }

    printf("%d\n", res_size);
    for (int i = 0; i < res_size; i++) {
        printf("%d ", res[i]);
    }

    free(res);
    freeHashTable(table);

    return 0;
}