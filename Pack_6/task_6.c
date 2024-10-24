#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tokens_s {
    int num;
    char **arr;
} Tokens;

// определяет, буква это или нет
int is_alpha(char c, const char *delims) {
    for (int i = 0; i < 4; i++) {
        if (c == delims[i]) return 0;
    }
    return 1;
}

void tokensSplit(Tokens *tokens, const char *str, const char *delims) {
    if (tokens->arr == NULL) { // подсчёт слов в строке
        int alpha = 0;
        int j = 0;
        for (int i = 0; str[i] != '\0';) {
            if (is_alpha(str[i], delims)) {
                if (alpha == 0) {
                    j = i;
                    alpha = 1;
                    tokens->num++;
                    while (is_alpha(str[j], delims) && str[j] != '\0') {
                        j++;
                    }
                    i = j;
                }
            } else {
                alpha = 0;
                i++;
            }
        }
    } else { // вычленение слов из строки
        int alpha = 0;
        int j = 0;
        int cnt = 0;
        int t = 0;
        for (int i = 0; str[i] != '\0';) {
            if (is_alpha(str[i], delims)) {
                if (alpha == 0) {
                    j = i;
                    alpha = 1;

                    while (is_alpha(str[j], delims) && str[j] != '\0') {
                        t++;
                        j++;
                    }

                    tokens->arr[cnt] = (char *) malloc((t+1) * sizeof(char));
                    strncpy(tokens->arr[cnt], &str[i], t);
                    tokens->arr[cnt][t] = '\0';

                    i = j;
                    cnt++;
                    t = 0;
                }
            } else {
                alpha = 0;
                i++;
            }
        }
    }
}

void tokensFree(Tokens *tokens) {
    if (tokens->arr == NULL) return; // если уже очищали, не надо
    for (int i = 0; i < tokens->num; i++) {
        free(tokens->arr[i]);
    }
    free(tokens->arr);
    tokens->arr = NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char delims[4] = ".,;:";

    Tokens tokens;
    tokens.num = 0;
    tokens.arr = NULL;

    char str[1000000]; // строка

    scanf("%s", str);
    
    tokensSplit(&tokens, str, delims);

    tokens.arr = (char **) malloc(tokens.num * sizeof(char *));

    tokensSplit(&tokens, str, delims);

    // вывод количество строк, а затем сами слова
    printf("%d\n", tokens.num);
    for (int i = 0; i < tokens.num; i++) {
        printf("%s\n", tokens.arr[i]);
    }

    tokensFree(&tokens);

    return 0;
}