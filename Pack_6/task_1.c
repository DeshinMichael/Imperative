#include <stdio.h>

typedef struct Node_s {
    double value;
    int next;
} Node;

int main() {
    int n, first;
    scanf("%d %d", &n, &first);
    
    Node list[n];

    // заполнение массива
    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &list[i].value, &list[i].next);
    }

    // вывод списка
    for (int i = first; i >= 0; i = list[i].next) {
        printf("%0.3lf\n", list[i].value);
    }

    return 0;
}