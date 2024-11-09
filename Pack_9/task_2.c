#include <stdio.h>
#include <stdlib.h>

int partition(int *a, int n, int pivot) {
    int *left = (int *) malloc(n * sizeof(int));
    int *right = (int *) malloc(n * sizeof(int));

    int i_left = 0;
    int i_right = 0;
    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < pivot) {
            left[i_left] = a[i];
            i_left++;
        } else if (a[i] > pivot) {
            right[i_right] = a[i];
            i_right++;
        } else {
            if (flag == 0) {
                left[i_left] = a[i];
                i_left++;
                flag = !flag;
            } else {
                right[i_right] = a[i];
                i_right++;
                flag = !flag;
            }
        }
    }

    for (int i = 0; i < i_left; i++) {
        a[i] = left[i];
    }

    int j = i_left;
    for (int i = 0; i < i_right; i++) {
        a[j] = right[i];
        j++;
    }

    free(left);
    free(right);

    return i_left;
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");

    int n, p;
    fread(&n, sizeof(int), 1, input);
    fread(&p, sizeof(int), 1, input);

    int *a = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fread(&a[i], sizeof(int), 1, input);
    }

    int k = partition(a, n, p);
    fwrite(&k, sizeof(int), 1, output);
    for (int i = 0; i < n; i++) {
        fwrite(&a[i], sizeof(int), 1, output);
    }

    fclose(input);
    fclose(output);

    free(a);

    return 0;
}