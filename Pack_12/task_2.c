#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree_node_t {
    int key;
    int count;
    struct tree_node_t* l;
    struct tree_node_t* r;
} tree_node;

tree_node *init_tree(int key) {
    tree_node *root = (tree_node *) malloc(sizeof(tree_node));
    root->key = key;
    root->count = 1;
    root->l = NULL;
    root->r = NULL;
    return root;
}

void insert(tree_node **root, int key) {
    if (*root == NULL) {
        *root = (tree_node *) malloc(sizeof(tree_node));
        (*root)->key = key;
        (*root)->count = 1;
        (*root)->l = NULL;
        (*root)->r = NULL;
    } else if (key < (*root)->key) {
        insert(&(*root)->l, key);
    } else if (key > (*root)->key) {
        insert(&(*root)->r, key);
    } else {
        (*root)->count++;
    }
}

void print_tree_to_arr(tree_node *root, int *arr, int *k) {
    if (root == NULL) {
        return;
    }
    print_tree_to_arr(root->l, arr, k);
    for (int i = 0; i < root->count; i++) {
        arr[(*k)++] = root->key;
    }
    print_tree_to_arr(root->r, arr, k);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int pos = rand() % (i + 1);
        swap(&arr[i], &arr[pos]);
    }
}

void free_tree(tree_node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->l);
    free_tree(root->r);
    free(root);
}

int main() {
    FILE* input = fopen("input.bin", "rb");
    FILE* output = fopen("output.bin", "wb");

    int n;
    fread(&n, sizeof(int), 1, input);

    int *arr = (int *) malloc(n * sizeof(int));
    fread(arr, sizeof(int), n, input);

    srand(time(0));
    shuffle(arr, n);

    tree_node *root = init_tree(arr[0]);
    for (int i = 1; i < n; i++) {
        insert(&root, arr[i]);
    }

    int k = 0;
    print_tree_to_arr(root, arr, &k);
    fwrite(arr, sizeof(int), n, output);

    free_tree(root);
    free(arr);

    fclose(output);
    fclose(input);
    
    return 0;
}