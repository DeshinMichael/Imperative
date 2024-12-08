#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int *heap, int *size, int elem) {
    heap[*size] = elem;
    (*size)++;
    siftUp(heap, *size-1);
}

void siftUp(int *heap, int index) {
    if (index == 0) return;
    int i_parent = (index-1) / 2;
    if (heap[index] < heap[i_parent]) {
        swap(&heap[index], &heap[i_parent]);
        siftUp(heap, i_parent);
    }
}

int extractMin(int *heap, int *size) {
    int res = heap[0];
    swap(&heap[0], &heap[*size-1]);
    (*size)--;
    siftDown(heap, size, 0);
    return res;
}

void siftDown(int *heap, int *size, int index) {
    int i_l_son = 2 * index + 1;
    int i_r_son = 2 * index + 2;

    int i_min_son;
    if (i_l_son >= *size && i_r_son >= *size) {
        return;
    } else if (i_l_son >= *size) {
        i_min_son = i_r_son;
    } else if (i_r_son >= *size) {
        i_min_son = i_l_son;
    } else {
        i_min_son = (heap[i_l_son] < heap[i_r_son]) ? i_l_son : i_r_son;
    }

    if (heap[index] > heap[i_min_son]) {
        swap(&heap[index], &heap[i_min_son]);
        siftDown(heap, size, i_min_son);
    }
}

int main() {
    FILE* input = fopen("input.bin", "rb");
    FILE* output = fopen("output.bin", "wb");
    
    int n;
    fread(&n, sizeof(int), 1, input);

    int *arr = (int *) malloc(n * sizeof(int));
    fread(arr, sizeof(int), n, input);

    int *heap = (int *) malloc(n * sizeof(int));
    int size = 0;
    for (int i = 0; i < n; i++) {
        insert(heap, &size, arr[i]);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = extractMin(heap, &size);
        fwrite(&arr[i], sizeof(int), 1, output);
    }

    free(arr);
    free(heap);

    return 0;
}