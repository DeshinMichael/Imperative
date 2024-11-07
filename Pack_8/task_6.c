#include <stdio.h>
#include <stdint.h>

uint32_t fixSoftErrors(uint32_t code, int bytes) {
    if (code > 0x10FFFF || (code >= 0xD800 && code <= 0xDFFF) ||
    (code <= 0x7F && bytes > 1) ||
    (code <= 0x7FF && bytes > 2) ||
    (code <= 0xFFFF && bytes > 3)) {
        return 0xFFFD;
    }
    return code;
}

void utf8ToUtf32le(FILE* input, FILE* output) {
    uint8_t c;
    while (fread(&c, sizeof(uint8_t), 1, input) > 0) {
        uint32_t code = 0;
        int bytes = 0;

        if ((c & 0b10000000) == 0) {
            code = c;
            bytes = 1;
        } else if ((c & 0b11100000) == 0b11000000) {
            code = c & 0b00011111;
            bytes = 2;
        } else if ((c & 0b11110000) == 0b11100000) {
            code = c & 0b00001111;
            bytes = 3;
        } else if ((c & 0b11111000) == 0b11110000) {
            code = c & 0b00000111;
            bytes = 4;
        } else {
            return;
        }

        uint8_t next_byte;
        for (int i = 1; i < bytes; i++) {
            size_t check = fread(&next_byte, sizeof(uint8_t), 1, input);
            
            if (check == 0) return;

            if ((next_byte & 0b11000000) != 0b10000000) return;

            code = (code << 6) | (next_byte & 0b00111111);
        }

        code = fixSoftErrors(code, bytes);

        fwrite(&code, sizeof(uint32_t), 1, output);   
    }
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    FILE* output = fopen("output.txt", "wb");

    utf8ToUtf32le(input, output);

    fclose(input);
    fclose(output);

    return 0;
}