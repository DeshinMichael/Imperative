#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int value;
    int prev;
    int next;
} Node;

// добавление узла спереди
int insert_front(Node *list, int curr_i, int new_i, int val, int *f, int *l) {
    list[new_i].value = val;
    if (curr_i == 0) { // сдвиг индексов первого и последнего узла
        *f = new_i;
    } 
    if (curr_i == *l) {
        *l = new_i;
    }
    int next_i = list[curr_i].next;
    list[new_i].next = next_i;
    list[new_i].prev = curr_i;
    list[next_i].prev = new_i;
    list[curr_i].next = new_i;
    return new_i-1;
}

// добавление узла сзади
int insert_back(Node *list, int curr_i, int new_i, int val, int *f, int *l) {
    list[new_i].value = val;
    if (curr_i == 0) { // сдвиг индексов первого и последнего узла
        *l = new_i;
    } 
    if (curr_i == *f) {
        *f = new_i;
    }
    int prev_i = list[curr_i].prev;
    list[new_i].prev = prev_i;
    list[new_i].next = curr_i;
    list[prev_i].next = new_i;
    list[curr_i].prev = new_i;
    return new_i-1;
}

// удаление узла
int erase(Node *list, int del_i, int *f, int *l) {
    int next_i = list[del_i].next;
    int prev_i = list[del_i].prev;
    if (del_i == *l) *l = prev_i; // сдвиг индексов первого и последнего узла
    if (del_i == *f) *f = next_i;
    list[prev_i].next = next_i;
    list[next_i].prev = prev_i;
    return list[del_i].value;
}

// вывод списка
void print_list(Node *list, int f) {
    for (int i = f; i != 0; i = list[i].next) {
        printf("%d\n", list[i].value);
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t; 
    int n, f, l, q;
    int oper, curr_i, new_i, val;
    Node *list;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d %d %d %d", &n, &f, &l, &q);
        new_i = n+1;
        f++;
        l++;

        list = (Node *) malloc((n+q+1) * sizeof(Node)); // сдвиг на 1

        // добавление вспомогательного узла
        list[0].next = f;
        list[0].prev = l;

        // заполнение списка
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &list[i].value, &list[i].next, &list[i].prev);
            list[i].prev++;
            list[i].next++; 
        }

        // проход операций
        for (int i = 0; i < q; i++) {
            scanf("%d", &oper);

            switch (oper) {
                case 1: // добавление спереди
                    scanf("%d %d", &curr_i, &val);
                    printf("%d\n", insert_front(list, curr_i+1, new_i, val, &f, &l));
                    new_i++;
                    break;
                case -1: // добавление сзади
                    scanf("%d %d", &curr_i, &val);
                    printf("%d\n", insert_back(list, curr_i+1, new_i, val, &f, &l));
                    new_i++;
                    break;
                case 0: // удаление
                    scanf("%d", &curr_i);
                    printf("%d\n", erase(list, curr_i+1, &f, &l));
                    break;
            }
        }
        printf("===\n");
        print_list(list, f);
        printf("===\n");

        free(list); // освобождение списка
    }

    return 0;
}