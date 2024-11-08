#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

typedef uint8_t byte;
typedef uint8_t bool;

typedef struct bitword_s{
    uint64_t value;
    uint32_t size;
}bitword;
const bitword NULL_BITWORD = {0,0};

void ReadBitword(FILE *stream,bitword *out);
bool WriteBitword(FILE *stream, bitword word);


bool WriteBitword(FILE *stream, bitword word){
    static byte prev_byte = 0;
    static byte prev_byte_size = 0;

    if (word.size == NULL_BITWORD.size){
        fwrite(&prev_byte,1,1,stream);
        return 0;
    }

    while (word.size > 0){

        if (word.value % 2){
            prev_byte |= 1 << (prev_byte_size);
        } 

        word.value >>= 1;
        prev_byte_size++;
        word.size--;

        if (prev_byte_size == 8){
            fwrite(&prev_byte,1,1,stream);
            prev_byte = 0;
            prev_byte_size = 0;
        }
    }

    return prev_byte_size == 0 ? 0 : 1;
}

void ReadBitword(FILE *stream,bitword *out){
    out->value = 0;
    fread(&out->size,sizeof(uint32_t),1,stream);

    for (uint32_t i = 0;i < out->size;i++){
        byte buff;
        fread(&buff,1,1,stream);

        if (buff){
            out->value |= 1 << i;
        }    
    }
}

int main(){
    FILE *in_file = fopen("1.in","rb");

    uint32_t words_count;
    fread(&words_count,sizeof(uint32_t),1,in_file);
    bitword *alphabet = malloc(sizeof(bitword) * words_count);

    for (uint32_t i = 0;i < words_count;i++){
        ReadBitword(in_file,alphabet + i);
    }

    FILE *out_file = fopen("output.bin","wb");

    uint32_t words_to_encode;
    fread(&words_to_encode,sizeof(uint32_t),1,in_file);
    
    bool byte_not_writed = 0;

    uint32_t writed = 0;

    for (;words_to_encode > 0;words_to_encode--){
        uint16_t buffer;
        fread(&buffer,sizeof(uint16_t),1,in_file);

        byte_not_writed = WriteBitword(out_file,alphabet[buffer]);
        writed += alphabet[buffer].size;
    }

    if (writed % 8 != 0){
        WriteBitword(out_file,NULL_BITWORD);
    }
    //printf("WRITED: %d\n",writed);
    fclose(in_file);
    fclose(out_file);
    free(alphabet);
    return 0;
}