#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 1000001

int main() {

    char ***arr = (char ***) malloc(L * sizeof(char **)); // двумерный массив строк

    int *size = (int *) calloc(L, sizeof(int)); // для текущего размера

    int *capacity = (int *) calloc(L, sizeof(int)); // для выделения размера

    int n, key; // n, ключ
    char value[8]; // значение
    scanf("%d", &n);

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &key, value);

        // выделение памяти, если нет записей
        if (capacity[key] == 0) {
            capacity[key] = 2;
            arr[key] = (char **) malloc(capacity[key] * sizeof(char *));
        }

        // выделение памяти, когда массив заполнен
        if (size[key] == capacity[key]) {
            capacity[key] *= 2;
            arr[key] = (char **) realloc(arr[key], capacity[key] * sizeof(char *));
        }

        arr[key][size[key]] = strdup(value); // копирование строки
        size[key]++; // увеличение размера
    }

    // вывод
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < size[i]; j++) {
            printf("%d %s\n", i, arr[i][j]);
            free(arr[i][j]);
        }
        free(arr[i]);
    }

    free(arr);
    free(size);
    free(capacity);

    return 0;
}