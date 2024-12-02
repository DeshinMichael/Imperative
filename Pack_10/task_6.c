#include <stdio.h>
#include <stdlib.h>

void add_edge(int **adj_list, int *in_degree, int from, int to) {
    if (!adj_list[from][to]) {
        adj_list[from][to] = 1;
        in_degree[to]++;
    }
}

void add_to_sorted_list(int *list, int *size, int theme) {
    int i = *size - 1;
    while (i >= 0 && list[i] > theme) {
        list[i+1] = list[i];
        i--;
    }
    list[i+1] = theme;
    (*size)++;
}

int extract_min(int *list, int *size) {
    int min = list[0];
    for (int i = 1; i < *size; i++) {
        list[i-1] = list[i];
    }
    (*size)--;
    return min;
}

void topological_sort(int **adj_matrix, int *in_degree, int *sorted_list, int *list_size, int n, int *count_in_list, int *res) {
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            add_to_sorted_list(sorted_list, list_size, i);
        }
    }

    while (*list_size > 0) {
        int curr = extract_min(sorted_list, list_size);
        res[*count_in_list] = curr;
        (*count_in_list)++;

        for (int i = 1; i <= n; i++) {
            if (adj_matrix[curr][i]) {
                in_degree[i]--;
                if (in_degree[i] == 0) {
                    add_to_sorted_list(sorted_list, list_size, i);
                }
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int *in_degree = (int *) calloc((n+1), sizeof(int));

    int **adj_matrix = (int **) malloc((n+1) * sizeof(int *));
    for (int i = 1; i <= n; i++) {
        adj_matrix[i] = (int *) calloc((n+1), sizeof(int));
    }

    int *sorted_list = (int *) malloc((n+1) * sizeof(int));
    int list_size = 0;

    int *res = (int *) malloc(n * sizeof(int));
    int count_in_list = 0;

    int b, a;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &b, &a);
        add_edge(adj_matrix, in_degree, b, a);
    }

    topological_sort(adj_matrix, in_degree, sorted_list, &list_size, n, &count_in_list, res);

    if (count_in_list < n) {
        printf("bad course");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d ", res[i]);
        }
    }

    free(in_degree);
    free(sorted_list);
    for (int i = 1; i <= n; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    free(res);

    return 0;
}