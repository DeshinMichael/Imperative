#include <stdio.h>
#include <string.h>

typedef struct Label_s {
    char name[16];
    int age;
} Label;

typedef struct NameStats_s {
    int cntTotal;
    int cntLong;
} NameStats;

typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;
} AgeStats;

// подсчёт статистики
void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges) {
    for (int i = 0; i < cnt; i++) {
        (*oNames).cntTotal++;
        (*oAges).cntTotal++;
        if (strlen(arr[i].name) > 10)
            (*oNames).cntLong++;
        if (arr[i].age >= 18)
            (*oAges).cntAdults++;
        if (arr[i].age < 14)
            (*oAges).cntKids++;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Label arr[1000];
    NameStats name_stats;
    AgeStats age_stats;

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%s %d let", arr[i].name, &arr[i].age);
    }

    calcStats(arr, n, &name_stats, &age_stats);

    // вывод
    printf("names: total = %d\n", name_stats.cntTotal);
    printf("names: long = %d\n", name_stats.cntLong);
    printf("ages: total = %d\n", age_stats.cntTotal);
    printf("ages: adult = %d\n", age_stats.cntAdults);
    printf("ages: kid = %d", age_stats.cntKids);

    return 0;
}