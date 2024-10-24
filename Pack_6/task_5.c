#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 1000001

typedef struct Node_t {
    char value[8];
    int next;
} Node;

// добавление узла
void insert(Node *list, int new_i, char *val) {
    strcpy(list[new_i].value, val);
    list[new_i].next = new_i+1;
}

// вывод списка
void print_list(Node *list, int size, int key) {
    for (int i = 0; i < size; i = list[i].next) {
        printf("%d %s\n", key, list[i].value);
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    Node **lists = (Node **) malloc(L * sizeof(Node *)); // массив списков
    int *curr_size = (int *) calloc(L, sizeof(int)); // массив текущих размеров
    int *capacity = (int *) calloc(L, sizeof(int)); // массив вместимостей

    int key;
    char val[8];
    int max_key = -1; // максимальный ключ

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &key, val);

        if (key > max_key) max_key = key; // проверка на максимальный ключ

        if (capacity[key] == 0) { // если пока ещё не было узлов
            capacity[key] = 2;
            lists[key] = (Node *) malloc(capacity[key] * sizeof(Node));
        }

        if (curr_size[key] == capacity[key]) { // если закончилось место
            capacity[key] *= 2; // увеличение вместимости на 2
            lists[key] = (Node *) realloc(lists[key], capacity[key] * sizeof(Node));
        }

        insert(lists[key], curr_size[key], val); // добавление узла
        curr_size[key]++; // увеличение размера
    }

    // вывод списков
    for (int i = 0; i <= max_key; i++) {
        print_list(lists[i], curr_size[i], i);
        free(lists[i]);
    }

    // освобождение памяти
    free(lists);
    free(curr_size);
    free(capacity);

    return 0;
}