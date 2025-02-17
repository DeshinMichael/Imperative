#include <stdio.h>
#include <stdlib.h>

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    char c;
    char args[50][101] = {0};

    int argi = 0;
    while ((c = getchar()) != EOF && c != '\0' && c != '\n') {
        while (c == ' ' && (c = getchar()) != EOF && c != '\0' && c != '\n');

        if (c == EOF || c == '\0' || c == '\n') break;

        int i = 0;

        if (c == '"') {
            while ((c = getchar()) != EOF && c != '"' && c != '\0' && c != '\n') {
                args[argi][i++] = c;
            }
        } else {
            do {
                args[argi][i++] = c;
            } while ((c = getchar()) != EOF && c != ' ' && c != '\0' && c != '\n');
        }
        args[argi][i] = '\0';
        argi++;

        if (c == EOF || c == '\0' || c == '\n') break;
    }
    
    for (int i = 0; i < argi; i++) {
        printf("[%s]\n", args[i]);
    }

    return 0;
}