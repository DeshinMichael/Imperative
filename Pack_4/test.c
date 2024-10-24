#include <stdio.h>

typedef struct LongNum_s {
    int len;
    int arr[200];
    int sign;
} LongNum;

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

    if (res->arr[res->len-1] == 0) {
        res->len--;
    }
}

void sub_in_col(LongNum *num1, LongNum *num2, LongNum *res) {
    int carry = 0, sub = 0;
    int l1 = num1->len;
    int l2 = num2->len;
    int dig1, dig2;

    for (int i = 0; i < l1; i++) {
        dig1 = num1->arr[i];
        dig2 = (i < l2) ? num2->arr[i] : 0;

        sub = dig1 - carry - dig2;

        if (sub < 0) {
            sub = dig1 + 10 - carry - dig2;
            res->arr[i] = sub % 10;
            carry = 1;
        } else {
            res->arr[i] = sub % 10;
            carry = 0;
        }
    }

    res->len = l1;
    while (res->len > 1 && res->arr[res->len-1] == 0) {
        res->len--;
    }
}

void print_long_num(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

int main() {
    LongNum nums[2];
    LongNum res;

    char n1[200];
    char n2[200];

    scanf("%s", n1);
    scanf("%s", n2);

    nums[0].len = strlen(n1);
    nums[1].len = strlen(n2);

    for (int i = 0; i < nums[0].len; i++) {
        nums[0].arr[i] = n1[nums[0].len - 1 - i] - '0';
    }
    for (int i = 0; i < nums[1].len; i++) {
        nums[1].arr[i] = n2[nums[1].len - 1 - i] - '0';
    }

    sub_in_col(&nums[0], &nums[1], &res);

    print_long_num(&res);
    
    return 0;
}