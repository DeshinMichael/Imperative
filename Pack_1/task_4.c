#include <stdio.h>

int main() {
    int n, is_simple = 1;
    scanf("%d", &n);
    for (int i = 2; i*i <= n; i++) { //перебор до корня
        if (n % i == 0) {
            is_simple = 0;
            break;
        }
    }
    if (is_simple == 1 && n != 1) { //результат проверки
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}