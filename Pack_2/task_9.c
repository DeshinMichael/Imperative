#include <stdio.h>

#define L 1000000

//функция возведения в степень
int pow(int n, int p) {
    int res = 1;
    for (int i = 0; i < p; i++) {
        res *= n;
    }
    return res;
}

//перевод в десятичную
int toTen(char *N, int p, int k) {
    int res = 0;
    int j = 0;
    for (int i = k-1; i >= 0; i--) { 
        res += (N[i]-'0') * pow(p, j);
        j++; 
    }
    return res;
}



int main() {

    int p, q, k; //из которой, в которую, количество символов N
    char N[L], s; //число, символ числа
    scanf("%d %d ", &p, &q);

    //ввод данных
    for (int i = 0; i < L; i++) {
        scanf("%c", &s);
        if (s == '\n') {
            break;
        }
        N[i] = s;
        k++;
    }

    printf("%d", toTen(N, p, k));

    return 0;
}