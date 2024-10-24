#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define L 1000002

// функция поиска слов и их вывода
void find_word_and_print(char *str) {
    int i = 0; // основной индекс
    int j = 0; // вспомогательный индекс
    int k = 0; // количество букв
    int k_upper = 0; // количество заглавных букв
    int flag = 0; // флажок

    // перебор всей строки
    while (str[i] != '\0') {
        if (isalpha(str[i])) {
            if (flag == 0) {
                j = i;
                flag = 1;

                // подсчёт
                while (isalpha(str[j])) {
                    if (isupper(str[j]))
                        k_upper++;
                    k++;
                    j++;
                }

                // вывод параметров
                printf("%d/%d ", k_upper, k);

                // вывод слова
                for (int t = i; t < j; t++){
                    printf("%c", str[t]);
                }
                printf("\n");
            }
        } else {
            flag = 0;
        }

        // обнуление счётчиков
        k = 0;
        k_upper = 0;
        
        i++;
    }
}

int main() {
    char str[L];
    scanf("%s", str);

    // функция
    find_word_and_print(str);

    return 0;
}