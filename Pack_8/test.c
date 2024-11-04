#include <stdio.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct MyFile_t
{
    char name[21];
    uint64_t size;
    uint8_t dir_or_not;
    uint64_t time_created;
    uint64_t time_changed;
    uint8_t hide_or_not;
} MyFile;
#pragma pack(pop)

int main()
{
    FILE *input = fopen("1.in", "rb");

    uint32_t N;
    fread(&N, sizeof(uint32_t), 1, input);

    uint64_t A;
    uint64_t B;

    fread(&A, sizeof(uint64_t), 1, input);
    fread(&B, sizeof(uint64_t), 1, input);

    MyFile res[N];
    MyFile arr[N];
    fread(&arr, sizeof(MyFile), N, input);

    int k = 0;
    for (int i = 0; i < N; i++)
    {
        MyFile cur = arr[i];

        if (cur.hide_or_not == 0 && cur.dir_or_not == 0 && cur.time_created >= A && cur.time_changed <= B)
        {
            res[k] = cur;
            k++;
        }
    }

    fclose(input);

    for (int i = 0; i < k - 1; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (strcmp(res[i].name, res[j].name) > 0)
            {
                MyFile buf = res[i];
                res[i] = res[j];
                res[j] = buf;
            }
        }
    }

    FILE *output = fopen("output.bin", "wb");
    fwrite(res, sizeof(MyFile), k, output);
    fclose(output);
}