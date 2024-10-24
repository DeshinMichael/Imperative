#include <stdio.h>

#define L 1000000

int pow(int n, int p) {
    int j = 1;
    for (int i = 0; i < p; i++) {
        j *= n;
    }
    return j;
}

int toTen(char N[], int p, int k) {
    int res = 0;
    int j = 0;
    for (int i = k-1; i >= 0; i--) { 
        res += (N[i]-'0') * pow(p, j);
        j++; 
    }
    return res;
}

int fromTen(int M[], int q) {
    
}

int main() {

    int p, q, k = 0; //из которой, в которую, количество символов N
    char N[L], M[L], s; //число до 10, число после 10, символ числа
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