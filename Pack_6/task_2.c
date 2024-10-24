#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_t {
    char value[8];
    int next;
} Node;

// добавление узла
int insert(Node *list, int curr_i, int new_i, char *val, int *f) {
    strcpy(list[new_i].value, val);
    if (curr_i == -1) {
        list[new_i].next = *f;
        *f = new_i;
    } else {
        list[new_i].next = list[curr_i].next;
        list[curr_i].next = new_i;
    }

    return new_i;
}

// удаление узла
char* erase(Node *list, int curr_i, int *f) {
    int del_i;
    if (curr_i == -1) {
        del_i = *f;
        *f = list[del_i].next;
    } else {
        del_i = list[curr_i].next;
        list[curr_i].next = list[del_i].next;
    }

    return list[del_i].value;
}

// вывод списка
void print_list(Node *list, int f) {
    for (int i = f; i >= 0; i = list[i].next) {
        printf("%s\n", list[i].value);
    }
}

int main() {
    int t, n, f, q;
    Node *list;
    int oper;
    int curr_i;
    int new_i;
    char new_val[8];
    
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &n, &f, &q);
        new_i = n;

        list = (Node *) malloc((n + q) * sizeof(Node)); // список

        // заполнение списка
        for (int i = 0; i < n; i++) {
            scanf("%s %d", list[i].value, &list[i].next);
        }

        // проход операций
        for (int i = 0; i < q; i++) {
            scanf("%d", &oper);
            if (oper == 0) {
                scanf("%d %s", &curr_i, new_val);

                printf("%d\n", insert(list, curr_i, new_i, new_val, &f));
                new_i++;
            } else {
                scanf("%d", &curr_i);

                printf("%s\n", erase(list, curr_i, &f));
            }
        }
        printf("===\n");
        print_list(list, f);
        printf("===\n");

        free(list);
    }

    return 0;
}