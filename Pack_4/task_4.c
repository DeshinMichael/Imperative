#include <stdio.h>

char is_not_Prime[15000000] = {0}; // хранение всех чисел

int main() {
    int n, q, x;
    scanf("%d %d", &n, &q);

    // первые два числа
    is_not_Prime[0] = 1;
    is_not_Prime[1] = 1;

    // заполнение массива
    for (int i = 2; i*i <= n; i++) {
        if (is_not_Prime[i] == 0) {
            for (int j = i*i; j <= n; j += i) {
                is_not_Prime[j] = 1;
            }
        }
    }

    // ввод и вывод результата
    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        if (is_not_Prime[x] == 0) {
            printf("%d prime\n", x);
        } else {
            printf("%d not\n", x);
        }
    }

    return 0;
}