#include <stdio.h>

// функция проверки на простое число
int is_simple(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    // вывод простых чисел до числа n
    for (int i = 2; i <= n; i++) {
        if (is_simple(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}