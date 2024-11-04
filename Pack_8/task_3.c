#include <stdio.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct File_t {
    char title[21];
    uint64_t S;
    uint8_t is_directory;
    uint64_t C;
    uint64_t M;
    uint8_t is_secret;
} File;
#pragma pack(pop)

int is_bigger(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int min_len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < min_len; i++) {
        if (str1[i] > str2[i]) return 1;
        if (str1[i] < str2[i]) return 0;
    }

    if (len1 > len2) return 1;
    return 0;
}

void insert_sorted(File *res, int *len, File new_file) {
    int i = *len - 1;
    while (i >= 0 && is_bigger(res[i].title, new_file.title)) {
        res[i+1] = res[i];
        i--;
    }
    res[i+1] = new_file;
    (*len)++;
}

int main() {

    FILE* input = fopen("input.txt", "rb");

    uint32_t n; 
    uint64_t A, B;

    fread(&n, sizeof(uint32_t), 1, input);
    fread(&A, sizeof(uint64_t), 1, input);
    fread(&B, sizeof(uint64_t), 1, input);

    File files[n];
    fread(files, sizeof(File), n, input);
    fclose(input);

    File res[n];
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (files[i].is_directory == 0 && files[i].is_secret == 0 && files[i].C >= A && files[i].M <= B) {
            insert_sorted(res, &len, files[i]);
        }
    }

    FILE* output = fopen("output.txt", "wb");
    fwrite(res, sizeof(File), len, output);
    fclose(output);

    return 0;
}