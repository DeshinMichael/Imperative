#include <stdio.h>

void reverse(char *start, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = start[i];
        start[i] = start[len - i - 1];
        start[len - i - 1] = temp;
    }
}

int main() {
    int n = 60;
    printf("%c", (char)n);

    return 0;
}