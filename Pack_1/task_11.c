#include <stdio.h>

int main() {
    int n, count = 0;
    long long answer = 0; // количество боксов
    scanf("%d", &n);
    for (int a = 1; a * a * a <= n; a++) { // перебор до кубического корня
        for (int b = a; a * b * b <= n; b++) {
            count = n / (a * b);
            if (count > 0)
                answer += count - b + 1; // подсчёт боксов
        }
    }
    printf("%lld", answer);

    return 0;
}