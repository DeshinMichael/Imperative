#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef struct State {
    char *regs[256];
} State;

State state;

int main() {
    char str[1001];

    while (fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\r\n")] = '\0';

        char *words[5];
        int argc = 0;
        char *tok = strtok(str, " ");
        while (tok && argc < 5) {
            words[argc++] = tok;
            tok = strtok(NULL, " ");
        }

        char *plugin = "core";
        char *f_name = words[0];

        char *colon = strchr(words[0], ':');
        if (colon) {
            *colon = '\0';
            plugin = words[0];
            f_name = colon + 1;
        }

        char lib_name[36];
        snprintf(lib_name, sizeof(lib_name), "./%s.so", plugin);

        char symbol[33];
        snprintf(symbol, sizeof(symbol), "%s_%d", f_name, argc-1);

        void *handle = dlopen(lib_name, RTLD_LAZY);
        if (!handle) {
            printf("Missing plugin %s\n", plugin);
            continue;
        }

        void (*fn)();
        *(void **)(&fn) = dlsym(handle, symbol);
        if (!fn) {
            printf("Missing function %s in plugin %s\n", symbol, plugin);
            dlclose(handle);
            continue;
        }

        switch (argc - 1) {
            case 0:
                ((void (*)(State *))fn)(&state);
                break;
            case 1:
                ((void (*)(State *, char *))fn)(&state, words[1]);
                break;
            case 2:
                ((void (*)(State *, char *, char *))fn)(&state, words[1], words[2]);
                break;
            case 3:
                ((void (*)(State *, char *, char *, char *))fn)(&state, words[1], words[2], words[3]);
                break;
        }

        dlclose(handle);
    }

    return 0;
}