#include <stdio.h>
#include <string.h>

typedef struct LongNum_s {
    int len;
    int arr[2000];
} LongNum;

// умножение
void mult_in_col(LongNum *num1, LongNum *num2, LongNum *res) {
    res->len = num1->len + num2->len;

    for (int i = 0; i < res->len; i++) {
        res->arr[i] = 0;    
    }

    for (int i = 0; i < num1->len; i++) {
        for (int j = 0; j < num2->len; j++) {
            res->arr[i+j] += num1->arr[i] * num2->arr[j];
            res->arr[i+j+1] += res->arr[i+j] / 10;
            res->arr[i+j] %= 10;
        }
    }

    while (res->len > 1 && res->arr[res->len-1] == 0) {
        res->len--;
    }
}

// вывод
void print_long_num(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

int main() {

    LongNum nums[2]; //два вводимых числа
    LongNum res; // результат

    char n1[1001];
    char n2[1001];

    scanf("%s", n1);
    scanf("%s", n2);

    nums[0].len = strlen(n1);
    nums[1].len = strlen(n2);

    // ввод чисел
    for (int i = 0; i < nums[0].len; i++) {
        nums[0].arr[i] = n1[nums[0].len - 1 - i] - '0';
    }
    for (int i = 0; i < nums[1].len; i++) {
        nums[1].arr[i] = n2[nums[1].len - 1 - i] - '0';
    }

    mult_in_col(&nums[0], &nums[1], &res);

    print_long_num(&res);

    return 0;
}