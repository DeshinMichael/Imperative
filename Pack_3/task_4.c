#include <stdio.h>
#include <ctype.h>
#include <string.h>

int calcLetters (char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int l = 0; // длина строки

    *oLowerCnt = 0;
    *oUpperCnt = 0;
    *oDigitsCnt = 0;

    // подсчёт до конца строки
    while (iStr[l] != '\0') {
        if (islower(iStr[l])) { 
            (*oLowerCnt)++;
        } else if (isupper(iStr[l])) {
            (*oUpperCnt)++;
        } else if (isdigit(iStr[l])) {
            (*oDigitsCnt)++;
        }
        l++;
    }
    return l;
}
int main() {
    char iStr[102];
    int numb = 1; // нумерация

    while (fgets(iStr, 102, stdin) != NULL) {
        int len = strlen(iStr);

        if (len > 0 && iStr[len-1] == '\n') {
            iStr[len-1] = '\0';
        }

        int oLowerCnt, oUpperCnt, oDigitsCnt;

        int strLen = calcLetters(iStr, &oLowerCnt, &oUpperCnt, &oDigitsCnt);

        // вывод строки
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", numb, strLen, oUpperCnt+oLowerCnt, oLowerCnt, oUpperCnt, oDigitsCnt);

        numb++;
    }
    return 0;
}