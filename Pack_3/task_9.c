#include <stdio.h>

#define L 1001

// функция поиска цифр в числе
int k_digits(int el) {
    int k = 0;
    while (el > 0) {
        el /= 10;
        k++;
    }
    return k;
}

// функция поиска максимального
int find_max(int el, int max_el) {
    if (k_digits(el) > max_el)
        max_el = k_digits(el);
    return max_el;
}

// функция вывода разделителей между строками
void print_sep(int max_len1, int max_len2, int max_len3) {
    printf("+");
    for (int i = 0; i < max_len1 + 2; i++) {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < max_len2 + 2; i++) {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < max_len3 + 2; i++) {
        printf("-");
    }
    printf("+");
    printf("\n");
}

// функция вывода чисел в строке с разделителями
void print_nums_with_lines(int n1, int n2, int n3, int max_len1, int max_len2, int max_len3) {
    printf("|");
    for (int i = 0; i < max_len1 + 3 - k_digits(n1); i++) {
        if (i == max_len1 + 1 - k_digits(n1)) {
            printf("%d", n1);
        } else {
            printf(" ");
        }
    }
    printf("|");
    for (int i = 0; i < max_len2 + 3 - k_digits(n2); i++) {
        if (i == max_len2 + 1 - k_digits(n2)) {
            printf("%d", n2);
        } else {
            printf(" ");
        }
    }
    printf("|");
    for (int i = 0; i < max_len3 + 3 - k_digits(n3); i++) {
        if (i == max_len3 + 1 - k_digits(n3)) {
            printf("%d", n3);
        } else {
            printf(" ");
        }
    }
    printf("|");
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int k_id[L] = {0}; // количество фрагментов по id
    int sum_len[L] = {0}; // суммарная длительность по id
    int id, len; 
    int max_len_num1 = 0; // максимальная количество цифр в столбце №1
    int max_len_num2 = 0; // максимальная количество цифр в столбце №2
    int max_len_num3 = 0; // максимальная количество цифр в столбце №3

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &id, &len);
        k_id[id]++;
        sum_len[id] += len;
        max_len_num1 = find_max(id, max_len_num1);
        max_len_num2 = find_max(k_id[id], max_len_num2);
        max_len_num3 = find_max(sum_len[id], max_len_num3);
    }

    // вывод
    for (int i = 0; i < L; i++) {
        if (k_id[i] != 0 && sum_len[i] != 0) {
            print_sep(max_len_num1, max_len_num2, max_len_num3);
            print_nums_with_lines(i, k_id[i], sum_len[i], max_len_num1, max_len_num2, max_len_num3);
        }
    }
    print_sep(max_len_num1, max_len_num2, max_len_num3);

    return 0;
}