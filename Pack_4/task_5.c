#include <stdio.h>

typedef struct LongNum_s {
    int len;
    int arr[500];
} LongNum;

// сложение
void sum_in_col(LongNum *num1, LongNum *num2, LongNum *res) {
    int carry = 0, sum = 0;
    int l2 = num2->len;
    int dig1, dig2;

    for (int i = 0; i < l2; i++) {
        dig1 = num1->arr[i];
        dig2 = num2->arr[i];

        sum = dig1 + dig2 + carry;

        res->arr[i] = sum % 10;
        carry = sum / 10;
    }

    res->len = l2;
    if (carry > 0) {
        res->arr[res->len] = carry;
        res->len++;
    }
}

// вывод числа
void print_long_num(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

LongNum nums[2000];

int main() {
    int n;
    scanf("%d", &n);

    nums[0].len = 1;
    nums[0].arr[0] = 1;

    nums[1].len = 1;
    nums[1].arr[0] = 1;

    // заполнение массива
    for (int i = 2; i < n; i++) {
        sum_in_col(&nums[i-2], &nums[i-1], &nums[i]);
    }
    print_long_num(&nums[n-1]);

    return 0;
}