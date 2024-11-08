#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 1000001

typedef struct Node_t {
    char value[8];
    int next;
} Node;

typedef struct List_t {
    int size;
    int capacity;
} List;

void insert(Node **lists, List *desc_list, int key, char *value) {

    if (desc_list[key].capacity == 0) {
        desc_list[key].capacity = 2;
        lists[key] = (Node *) malloc(desc_list[key].capacity * sizeof(Node));
    }

    if (desc_list[key].size == desc_list[key].capacity) {
        desc_list[key].capacity *= 2;
        lists[key] = (Node *) realloc(lists[key], desc_list[key].capacity * sizeof(Node));
    }

    strcpy(lists[key][desc_list[key].size].value, value);
    lists[key][desc_list[key].size].next = desc_list[key].size + 1;
    desc_list[key].size++;

}

void print_list(Node *list, int size, int key) {
    for (int i = 0; i < size; i = list[i].next) {
        printf("%d %s\n", key, list[i].value);
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    Node **lists = (Node **) malloc(MAX_KEY * sizeof(Node *));
    List *desc_list = (List *) malloc(MAX_KEY * sizeof(List));

    for (int i = 0; i < MAX_KEY; i++) {
        lists[i] = NULL;
        desc_list[i].size = 0;
        desc_list[i].capacity = 0;
    }

    int key;
    char value[8];
    int max_key = -1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &key, value);

        if (key > max_key) max_key = key;

        insert(lists, desc_list, key, value);
    }

    for (int i = 0; i <= max_key; i++) {
        if (lists[i] != NULL) {
            print_list(lists[i], desc_list[i].size, i);
        }
        free(lists[i]);
    }

    free(lists);
    free(desc_list);

    return 0;
}