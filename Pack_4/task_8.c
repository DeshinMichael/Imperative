#include <stdio.h>
#include <string.h>

typedef struct LongNum_s {
    int len;
    int arr[200];
    int sign;
} LongNum;

// сумма
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

    if (res->arr[res->len-1] == 0)
        res->sign = 1;
}

// разность
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

// вывод числа
void print_long_num(LongNum *num) {
    if (num->sign == -1) {
        printf("-");
    }
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
    printf("\n");
}

// считывание строки в массив цифр
void char_to_int(LongNum *num1, char num[]) {
    num1->len = strlen(num);
    if (num[0] == '-') {
        num1->sign = -1;
        for (int i = 0; i < num1->len-1; i++) {
            num1->arr[i] = num[num1->len - 1 - i] - '0';
        }
        num1->len--;
    } else {
        num1->sign = 1;
        for (int i = 0; i < num1->len; i++) {
            num1->arr[i] = num[num1->len - 1 - i] - '0';
        }
    }
}

// сравнение чисел без знака
int compare_abs(LongNum *num1, LongNum *num2) {
    int len = (num1->len > num2->len) ? num1->len : num2->len;
    int dig1, dig2;
    if (num1->len > num2->len) {
        return 1;
    } else if (num1->len < num2->len) {
        return 2;
    }
    for (int i = len-1; i >= 0; i--) {
        dig1 = num1->arr[i];
        dig2 = num2->arr[i];
        if (dig1 > dig2) {
            return 1;
        } else if (dig1 < dig2) {
            return 2;
        }
    }
    return 0;
}

int main() {
    int n, t;
    int a, b;
    scanf("%d", &n);

    LongNum nums[1000];
    char num[200];

    for (int i = 0; i < n; i++) {
        scanf("%d", &t);
        switch (t) { // разные t
            case 0: // явное число
                scanf("%s", num);
                char_to_int(&nums[i], num);
                break;
            case 1: // сумма
                scanf("%d %d", &a, &b);
                if (nums[a].sign == nums[b].sign) {
                    if (compare_abs(&nums[a], &nums[b]) == 1) {
                        nums[i].sign = nums[a].sign;
                        sum_in_col(&nums[b], &nums[a], &nums[i]);
                    } else if (compare_abs(&nums[a], &nums[b]) == 2) {
                        nums[i].sign = nums[b].sign;
                        sum_in_col(&nums[a], &nums[b], &nums[i]);
                    } else {
                        nums[i].sign = nums[a].sign;
                        sum_in_col(&nums[a], &nums[b], &nums[i]);
                    }
                } else {
                    if (compare_abs(&nums[a], &nums[b]) == 1) {
                        nums[i].sign = nums[a].sign;
                        sub_in_col(&nums[a], &nums[b], &nums[i]);
                    } else if (compare_abs(&nums[a], &nums[b]) == 2) {
                        nums[i].sign = nums[b].sign;
                        sub_in_col(&nums[b], &nums[a], &nums[i]);
                    } else {
                        nums[i].sign = 1;
                        nums[i].len = 1;
                        nums[i].arr[0] = 0;
                    }
                }
                break;
            case 2: // разность
                scanf("%d %d", &a, &b);
                if (nums[a].sign != nums[b].sign) {
                    if (compare_abs(&nums[a], &nums[b]) == 1) {
                        nums[i].sign = nums[a].sign;
                        sum_in_col(&nums[b], &nums[a], &nums[i]);
                    } else if (compare_abs(&nums[a], &nums[b]) == 2) {
                        nums[i].sign = nums[b].sign * (-1);
                        sum_in_col(&nums[a], &nums[b], &nums[i]);          
                    } else {
                        nums[i].sign = nums[b].sign * (-1);
                        sum_in_col(&nums[a], &nums[b], &nums[i]);
                    }
                } else {
                    if (compare_abs(&nums[a], &nums[b]) == 1) {
                        nums[i].sign = nums[a].sign;
                        sub_in_col(&nums[a], &nums[b], &nums[i]);
                    } else if (compare_abs(&nums[a], &nums[b]) == 2) {
                        nums[i].sign = nums[b].sign * (-1);
                        sub_in_col(&nums[b], &nums[a], &nums[i]);          
                    } else {
                        nums[i].sign = 1;
                        nums[i].len = 1;
                        nums[i].arr[0] = 0;
                    }
                }
                break;
            case 3: // умножение
                scanf("%d %d", &a, &b);
                if (nums[a].sign == nums[b].sign) {
                    nums[i].sign = 1;
                    mult_in_col(&nums[a], &nums[b], &nums[i]);
                } else {
                    nums[i].sign = -1;
                    mult_in_col(&nums[a], &nums[b], &nums[i]);                    
                }
        }
    }

    // вывод
    for (int i = 0; i < n; i++) {
        print_long_num(&nums[i]);
    }

    return 0;
}