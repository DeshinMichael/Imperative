#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define L 1000000000

int main() {
    freopen("input.txt", "r", stdin);
    int p, q; //из которой, в которую
    char *n = (char *) malloc(L * sizeof(char)); //число

    scanf("%d %d %s", &p, &q, &n);

    return 0;
}