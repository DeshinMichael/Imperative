#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int *a, int left, int right) {
    int rand_i = left + rand() % (right - left + 1);
    swap(&a[rand_i], &a[right]);

    int pivot = a[right];
    int i = left-1;
    int flag = 1;

    for (int j = left; j < right; j++) {
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        } else if (a[j] == pivot) {
            if (!flag) {
                i++;
                swap(&a[i], &a[j]);
                flag = !flag;
            } else {
                flag = !flag;
            }
        }
    }
    swap(&a[i+1], &a[right]);
    return i+1;
}

void quickSort(int *a, int left, int right) {
    if (left < right) {
        int pivot_i = partition(a, left, right);

        quickSort(a, left, pivot_i-1);
        quickSort(a, pivot_i+1, right);
    }
}

long long sum_of_minimums(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n-1; i++) {
        sum += ((long long)a[i]) * (n-i-1);
    }
    return sum;
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, input);

    int *a = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fread(&a[i], sizeof(int), 1, input);
    }

    srand(time(0));
    quickSort(a, 0, n-1);

    for (int i = 0; i < n; i++) {
        fwrite(&a[i], sizeof(int), 1, output);
    }

    fclose(input);
    fclose(output);
    
    free(a);

    return 0;
}