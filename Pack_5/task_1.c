#include <stdio.h>
#include <string.h>

int main() {
    char s[4]; // первые 3 буквы
    char days_of_week[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}; // дни недели

    scanf("%s", s);

    for (int i = 0; i < 7; i++) {
        if (strcmp(s, days_of_week[i]) == 0) {
            printf("%d", i+1);
            break;
        }
    }
    
    return 0;
}