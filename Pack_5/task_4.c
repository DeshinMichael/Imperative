#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int n;
    scanf("%d", &n);

    long long *stack = (long long *) malloc(n * sizeof(long long)); // стек
    int top = 0; // верхний элемент стека
    long long ring = 1000000007; // для кольца вычетов
    char s[20]; // число

    for (int i = 0; i < n; i++) {
        scanf("%s", s);

        if (isdigit(s[0]) || (s[0] == '-' && isdigit(s[1]))) {
            long long str_num = strtol(s, NULL, 10); // перевод строки в число
            long long num = (str_num + ring) % ring;
            stack[++top] = num; // добавление числа в стек
        } else {
            long long a = stack[top--]; // беру верхнее число
            long long b = stack[top--]; // беру число под ним

            long long res; // для результата операции
            switch (s[0]) {
                case '+':
                    res = (b + a) % ring;
                    break;
                case '-':
                    res = (b - a + ring) % ring;
                    break;
                case '*':
                    res = (b * a) % ring;
                    break;
            }
            stack[++top] = res; // добавление числа в стек
        }
    }

    printf("%ld", stack[top]);

    free(stack);

    return 0;
}