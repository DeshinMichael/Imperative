#include <stdio.h>
#include <string.h>

#define L 16

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds) {
    int k_sep = 0; // количество разделителей
    int line_in_str = 0; // есть | или нет

    // подсчёт разделителей
    for (int i = 0; i < strlen(iStr); i++) {
        if (iStr[i] == ':')
            k_sep++;
        if (iStr[i] == '|')
            line_in_str = 1;
    }

    if (line_in_str == 1) { // при некорректном вводе
        *oHours = -1;
        *oMinutes = -1;
        *oSeconds = -1;
        return 0;
    } else {
        if (k_sep == 2) { // если два символа :
            sscanf(iStr, "%d:%d:%d", oHours, oMinutes, oSeconds);
            if (0 <= *oHours && *oHours <= 23 && 0 <= *oMinutes && *oMinutes <= 59 && 0 <= *oSeconds && *oSeconds <= 59) {
                return 1;
            } else {
                *oHours = -1;
                *oMinutes = -1;
                *oSeconds = -1;
                return 0;
            }
        }
        if (k_sep == 1) { // если один символ :
            sscanf(iStr, "%d:%d", oHours, oMinutes);
            if (0 <= *oHours && *oHours <= 23 && 0 <= *oMinutes && *oMinutes <= 59) {
                return 1;
            } else {
                *oHours = -1;
                *oMinutes = -1;
                *oSeconds = -1;
                return 0;
            }
        }
    }

}

int main() {
    char iStr[L];
    int oHours = 0, oMinutes = 0, oSeconds = 0; // создание локальных переменных

    fgets(iStr, L, stdin); // ввод строки

    int is_right = readTime(iStr, &oHours, &oMinutes, &oSeconds);

    // вывод
    printf("%d %d %d %d\n", is_right, oHours, oMinutes, oSeconds);
    printf("%d %d %d\n", is_right, oHours, oMinutes);
    printf("%d %d", is_right, oHours);

    return 0;
}