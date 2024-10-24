#include <stdio.h>

int main() {
    int n;
    double minus = 0, nul = 0, plus = 0; // отриц., нуль, полож.
    scanf("%d", &n);
    double n_d = n; // присваивание n переменной типа double
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        if (m < 0) {
            minus++;    
        } else if (m == 0) { 
            nul++;
        } else {
            plus++;
        }
    }
    minus = minus / n_d;
    nul = nul / n_d;
    plus = plus / n_d;
    printf("%0.5f %0.5f %0.5f", minus, nul, plus);

    return 0;
}