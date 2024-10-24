#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100000

// создание строки
void create_str(char **strs, int *str_cnt, int len, char *str) {
    strs[*str_cnt] = (char *) malloc((len+1) * sizeof(char)); // выделение памяти для строки
    strncpy(strs[*str_cnt], str, len); // копирование строки
    strs[*str_cnt][len] = '\0';
    (*str_cnt)++;
}

// удаление строки
void delete_str(char **strs, int id) {
    free(strs[id]);
    strs[id] = NULL; // для дальнейшего освобождения памяти
}

// вывод строки
void print_str(char **strs, int id) {
    printf("%s\n", strs[id]);
}

// подсчёт символа в строке
int count_c(char **strs, int id, char c) {
    int k = 0;
    for (int i = 0; strs[id][i] != '\0'; i++) {
        if (strs[id][i] == c) k++;
    }
    return k;
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, t;
    int len_s, id;
    char str[100001];
    char c;
    scanf("%d", &n);

    int str_cnt = 0;
    char **strs = (char **) malloc(MAX_LEN * sizeof(char *)); // массив строк

    for (int i = 0; i < n; i++) {
        scanf("%d", &t);

        switch (t) {
            case 0:
                scanf("%d %s", &len_s, str);
                create_str(strs, &str_cnt, len_s, str);
                break;
            case 1:
                scanf("%d", &id);
                delete_str(strs, id);
                break;
            case 2:
                scanf("%d", &id);
                print_str(strs, id);
                break;
            default:
                scanf("%d %c", &id, &c);
                printf("%d\n", count_c(strs, id, c));
                break;
        }
    }

    // освобождение памяти
    for (int i = 0; i < str_cnt; i++) {
        if (strs[i] != NULL) free(strs[i]);
    }
    free(strs);

    return 0;
}