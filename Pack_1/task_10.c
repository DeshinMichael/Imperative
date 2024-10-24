#include <stdio.h>

int main() {
    int h, m, s, k; // часы, минуты, секунды, k
    scanf("%d %d %d %d", &h, &m, &s, &k);
    int time_in_sec = h * 3600 + m * 60 + s + k; // время в секундах
    int s_to_h = time_in_sec / 3600; // секунды в часы
    int s_to_m = (time_in_sec - s_to_h * 3600) / 60; // секунды в минуты
    int sec = time_in_sec - s_to_h * 3600 - s_to_m * 60; // секунды
    if (s_to_h >= 24) { // вывод времени
        printf("%d %d %d", s_to_h % 24, s_to_m, sec);
    } else {
        printf("%d %d %d", s_to_h, s_to_m, sec);
    }

    return 0;
}