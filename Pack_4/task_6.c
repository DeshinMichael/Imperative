#include <stdio.h>

typedef struct LongNum_s {
    int len;
    int arr[3000];
} LongNum;

// умножение
void mult_in_col(LongNum *num1, LongNum *res, int n) {
    int carry = 0;
    int len = num1->len;
    int dig;

    for (int i = 0; i < len; i++) {
        dig = num1->arr[i];

        carry = carry + dig * n;
        res->arr[i] = carry % 10;
        carry /= 10;
    }

    res->len = len;
    while (carry > 0) {
        res->arr[res->len] = carry % 10;
        res->len++;
        carry /= 10;
    }
}

// вывод числа
void print_long_num(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

LongNum nums[1000];

int main() {
    int n;
    scanf("%d", &n);

    nums[0].len = 1;
    nums[0].arr[0] = 1;

    // заполнение массива
    for (int i = 1; i < n; i++) {
        mult_in_col(&nums[i-1], &nums[i], i+1);
    }

    print_long_num(&nums[n-1]);

    return 0;
}