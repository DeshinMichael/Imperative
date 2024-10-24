#include <stdio.h>

// разворот строки
void reverse(char *start, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = start[i];
        start[i] = start[len - i - 1];
        start[len - i - 1] = temp;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char str[1000][101];

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%s", &str[i]);
    }

    for (int i = 0; i < n; i++) {
        int len = 0;
        while (str[i][len] != '\0') { // считывание строк
            len++;
        }
        reverse(str[i], len);
    }

    // вывод
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]);
    }

    return 0;
}