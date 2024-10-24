#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    if (a % b == 0) { //деление нацело
        printf("%d %d %d 0", a/b, a/b, a/b);
    } else { //деление не нацело
        if (a > 0) {
            printf("%d %d %d %d", a/b, a/b+1, a/b, a%b);
        } else {
            printf("%d %d %d %d", a/b-1, a/b, a/b, a%b+b);
        }
    }

    return 0;
}