#include <stdio.h>

typedef struct DateTime_s {
    int year, month, day;
    int hours, minutes, seconds;
} DateTime;

// сравнение дат
int compare_dates(const DateTime *x, const DateTime *y) {
    if (x->year != y->year) return x->year - y->year;
    if (x->month != y->month) return x->month - y->month;
    if (x->day != y->day) return x->day - y->day;
    if (x->hours != y->hours) return x->hours - y->hours;
    if (x->minutes != y->minutes) return x->minutes - y->minutes;
    if (x->seconds != y->seconds) return x->seconds - y->seconds;
}

// вычисление минимальной даты
DateTime min(const DateTime *arr, int cnt) {
    DateTime min_date = arr[0];

    for (int i = 1; i < cnt; i++) {
        if (compare_dates(&arr[i], &min_date) < 0)
            min_date = arr[i];
    }
    
    return min_date;
}

int main() {
    int n;
    scanf("%d", &n);
    DateTime dates[50000]; 

    // ввод
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d %d", &dates[i].year, &dates[i].month, &dates[i].day, &dates[i].hours, &dates[i].minutes, &dates[i].seconds);
    }

    DateTime min_date = min(dates, n);

    // вывод
    printf("%d %d %d %d %d %d", min_date.year, min_date.month, min_date.day, min_date.hours, min_date.minutes, min_date.seconds);

    return 0;
}