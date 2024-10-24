#include <stdio.h>

int main()
{
    int n, min; // n, минимальный эл.
    scanf("%d %d", &n, &min);
    int max = min, min_i = 1, max_i = 1; // максимальный эл., индекс минимального, индекс максимального
    for (int i = 2; i <= n; ++i){
        int el;
        scanf("%d", &el);
        if (el > max){ // алгоритм поиска максимума
            max = el;
            max_i = i;
        }
        if (el < min){ // алгоритм поиска минимума
            min = el;
            min_i = i;
        }
    }
    printf("%d %d %d %d", min, min_i, max, max_i);
}