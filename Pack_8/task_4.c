#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void read_str(FILE* file, char *str) {
    int i = 0;
    while (1) {
        fread(&str[i], sizeof(char), 1, file);
        if (str[i] == '\0') break;
        i++;
    }
}

void parseBsonToGson(FILE* file) {
    int32_t size;
    fread(&size, sizeof(int32_t), 1, file);

    printf("{\n");

    int8_t T;
    int first_field = 1;
    while (1) {
        fread(&T, sizeof(int8_t), 1, file);
        if (T == 0) break;

        if (!first_field) printf(",\n");
        first_field = 0;

        char name[1024] = {'\0'};
        read_str(file, name);
        printf("    \"%s\": ", name);

        switch (T) {
            case 1: {
                double double_value;
                fread(&double_value, sizeof(double), 1, file);
                printf("%0.15g", double_value);
                break;
            }
            case 2: {
                int32_t L;
                fread(&L, sizeof(int32_t), 1, file);
                char *str_value = (char *) malloc(L * sizeof(char));
                read_str(file, str_value);
                printf("\"%s\"", str_value);
                free(str_value);
                break;
            }
            case 8: {
                int8_t value8;
                fread(&value8, sizeof(int8_t), 1, file);
                if (value8 == 1) printf("true");
                else printf("false");
                break;
            }
            case 10:
                printf("null");
                break;
            case 16: {
                int32_t value32;
                fread(&value32, sizeof(int32_t), 1, file);
                printf("%d", value32);
                break;
            }
            case 18: {
                int64_t value64;
                fread(&value64, sizeof(int64_t), 1, file);
                printf("%lld", value64);
                break;
            }
        } 
    }
    printf("\n}\n");
}

int main() {
    FILE* input = fopen("1.in", "rb");

    parseBsonToGson(input);

    fclose(input);

    return 0;
}