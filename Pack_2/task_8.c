#include <stdio.h>

int main() {
    int is_dot = 0;
    int k = 0;
    char s;
    while (1) {
        scanf("%c", &s);
        if (s == '\n') {
            break;
        } else if (s == '.') {
            if (is_dot == 1)
                is_dot = 0;
        } else {
            if (is_dot == 0) {
                is_dot = 1;
                k++;
            }
        }
    }
    printf("%d", k);

    return 0;
}