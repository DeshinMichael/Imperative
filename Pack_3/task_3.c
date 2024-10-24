#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(char *pref, char *suff) {
    
    while (*suff != '\0') {
        *pref = *suff;
        pref++;
        suff++;
    }

    *pref = '\0';

    return pref;
}

int main() {    
    int n;
    scanf("%d", &n);

    // двумерный массив
    char **strs = (char **)malloc(n * sizeof(char *));
    int res_len = 0; // длина итоговой строки

    // заполнение двумерного массива
    for (int i = 0; i < n; i++) {
        // одномерный массив
        strs[i] = (char *)malloc(101 * sizeof(char));
        scanf("%s", strs[i]);
        res_len += strlen(strs[i]);
    }

    char *res = (char *)malloc((res_len + 1) * sizeof(char)); // итоговая строка

    char *end = res;

    // конкатенация строк в одну
    for (int i = 0; i < n; i++) {
        end = concat(end, strs[i]);
        free(strs[i]); // очистка дин. памяти
    }
    free(strs); // очистка дин. памяти

    printf("%s", res);
    free(res); // очистка дин. памяти

    return 0;
}