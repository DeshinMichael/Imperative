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

uint32_t hash(uint32_t k) {
    return (7*k - 10) % P;
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
    uint32_t index = hash(key) % table->size;
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
    uint32_t index = hash(key) % table->size;
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

    FILE* input = fopen("input.bin", "rb");
    FILE* output = fopen("output.bin", "wb");

    int n;
    fread(&n, sizeof(int), 1, input);

    HashTable *table = createHashTable(n);
    int *res = (int *) malloc(n * sizeof(int));
    int res_size = 0;

    int key;
    for (int i = 0; i < n; i++) {
        fread(&key, sizeof(int), 1, input);
        if (!valueExists(table, key)) {
            insert(table, key);
            res[res_size++] = key;
        }
    }

    fwrite(&res_size, sizeof(int), 1, output);
    fwrite(res, sizeof(int), res_size, output);

    fclose(input);
    fclose(output);

    free(res);
    freeHashTable(table);

    return 0;
}