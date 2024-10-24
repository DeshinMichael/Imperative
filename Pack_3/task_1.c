#include <stdio.h>

// печать
void printTime(int h, int m, int s) {
    printf("%02d:%02d:%02d\n", h, m, s);
}

int main() {
    int n, h, m, s;
    scanf("%d", &n);
    int time[1001][3]; // хранение дат

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &time[i][0], &time[i][1], &time[i][2]);
    }

    // вывод
    for (int i = 0; i < n; i++) {
        printTime(time[i][0], time[i][1], time[i][2]);
    }

    return 0;
}