#include <stdio.h>
#include <string.h>

#define L 1000000

int main() {
    char str[L];
    int chars[127] = {0}; // для подсчёта количества букв

    // ввод строк и подсчёт букв
    while (fgets(str, sizeof(str), stdin) != NULL) {
        for (int i = 0; i < sizeof(str); i++) {
            if (str[i] == '\0')
                break;
            chars[str[i]]++;
        }
    }

    // вывод данных
    for (int i = 32; i < 127; i++) {
        if (chars[i] > 0) { 
            printf("%c ", (char) i);
            for (int j = 0; j < chars[i]; j++) {
                printf("#");
            }
            printf("\n");
        }
    }

    return 0;
}