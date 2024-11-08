#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define L 1000000

// возведение в степень
int power(int n, int p) {
    int res = 1;
    while (p) {
        res *= n;
        p--;
    }
    return res;
}

// перевод в десятичную
int to_ten(char *n, int p, int len) {
    int res = 0;
    int num, j = 0;
    for (int i = len-1; i >= 0; i--) {
        num = (n[i] >= '0' && n[i] <= '9') ? (n[i]-'0') : ((n[i] >= 'a' && n[i] <= 'z') ? (n[i]-'a'+10) : (n[i]-'A'+36));
        res += num * power(p, j);
        j++;
    }
    return res;
}

// перевод из десятичной
char *from_ten(int n, int q, char *res) {
    int ost, i = 0;
    while (n) {
        ost = n % q;
        res[i] = (ost >= 0 && ost <= 9) ? (char)(ost+'0') : ((ost >= 10 && ost <= 35) ? (char)(ost+'a'-10) : (char)(ost+'A'-36));
        n /= q;
        i++;
    }
    res[i] = '\0';
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    int p, q;
    char *n = (char *) malloc(L * sizeof(char));
    char *res = (char *) malloc(L * sizeof(char));

    scanf("%d %d %s", &p, &q, n);

    res = strcpy(res, from_ten(to_ten(n, p, strlen(n)), q, res));
    for (int i = strlen(res)-1; i >= 0; i--) { // вывод в обратном порядке
        printf("%c", res[i]);
    }

    free(n);
    free(res);

    return 0;
}