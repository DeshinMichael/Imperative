#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// поиск наименьшей строки лексикографически больше исходной
void find_smallest_big_str(char *str, int len) {
    int i = len-2;
    while (i >= 0 && str[i] >= str[i+1]) {
        i--;
    }

    int j = len-1;
    while (str[i] >= str[j]) {
        j--;
    }

    char temp = str[j];
    str[j] = str[i];
    str[i] = temp;

    for (int left = i+1, right = len-1; left < right; left++, right--) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    char *str = (char *) malloc((n+1) * sizeof(char));

    scanf("%c", &str[0]);
    for (int i = 0; i < n; i++) {
        scanf("%c ", &str[i]);
    }
    str[n] = '\0';

    find_smallest_big_str(str, n);

    for (int i = 0; i < n; i++) {
        printf("%c ", str[i]);
    }

    free(str);

    return 0;
}