#include <stdio.h>
#include <stdlib.h>

typedef struct Human_t {
    int value;
    struct Human_t *next; // указатель на следующего
} Human;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Human *people = (Human *) malloc(n * sizeof(Human));

    // заполнение массива людьми
    for (int i = 0; i < n; i++) {
        people[i].value = i+1;
        people[i].next = i < n-1 ? &people[i+1] : &people[0];
    }

    Human *curr = &people[0]; // первый человек

    // пока не останется один элемент
    while (curr->next != curr) { 

        // до к-го элемента
        for (int i = 0; i < k-2; i++) {
            curr = curr->next;
        }
        printf("%d\n", curr->next->value); // вывод выбывшего
        curr->next = curr->next->next; // удаление человека
        curr = curr->next; // переход к следующему
    }
    printf("%d", curr->value); // вывод последнего

    free(people);

    return 0;
}