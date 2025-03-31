#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    char *regs[256];
} State;

void concat_2(State *state, char *idx0, char *idx1) {
    int i = atoi(idx0);
    int j = atoi(idx1);

    char *a = state->regs[i] ? state->regs[i] : "";
    char *b = state->regs[j] ? state->regs[j] : "";

    char *result = malloc(strlen(a) + strlen(b) + 1);

    strcpy(result, a);
    strcat(result, b);

    free(state->regs[i]);
    state->regs[i] = result;
}

void tokenize_1(State *state, char *arg) {
    int count = 0;
    char *tmp = strdup(arg);
    char *token = strtok(tmp, "_");

    while (token && count < 255) {
        count++;
        free(state->regs[count]);            
        state->regs[count] = strdup(token);   
        token = strtok(NULL, "_");
    }

    char buf[4];
    sprintf(buf, "%d", count);
    free(state->regs[0]);
    state->regs[0] = strdup(buf);

    free(tmp);
}