#include <stdio.h>

int main(){
    int n, sum_ch = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        if (m % 2 == 0) {
            sum_ch += m; //сумма чётных чисел
        }
    }
    printf("%d", sum_ch);
    
    return 0;
}