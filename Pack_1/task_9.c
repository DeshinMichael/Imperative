#include <stdio.h>

int main() {
    int a1, a2, b1, b2, c1, c2;
    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);
    if (a1 >= b2 && a1 >= c2 && (b1 + c1) <= a2) { // 8 случаев
        printf("YES");
        return 0;
    }
    if (a1 >= b1 && a1 >= c1 && (b2 + c2) <= a2) {
        printf("YES");
        return 0;
    }
    if (a2 >= b2 && a2 >= c2 && (b1 + c1) <= a1) {
        printf("YES");
        return 0;
    }
    if (a2 >= b1 && a2 >= c1 && (b2 + c2) <= a1) {
        printf("YES");
        return 0;
    }
    if (a1 >= b2 && a1 >= c1 && (b1 + c2) <= a2) {
        printf("YES");
        return 0;
    }
    if (a1 >= b1 && a1 >= c2 && (b2 + c1) <= a2) {
        printf("YES");
        return 0;
    }
    if (a2 >= b2 && a2 >= c1 && (b1 + c2) <= a1) {
        printf("YES");
        return 0;
    }
    if (a2 >= b1 && a2 >= c2 && (b2 + c1) <= a1) {
        printf("YES");
        return 0;
    }
    printf("NO");
    return 0;
}