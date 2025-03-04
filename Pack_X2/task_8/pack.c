#include "pack.h"
#include <stdarg.h>
#include <string.h> 

int pack(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int num_of_bytes = 0;

    for (const char *c = format; *c != '\0'; c++) {
        if (*c == '%') {
            c++;

            if (*c == 'd') {
                int val = va_arg(args, int);
                num_of_bytes += 4;

                if (buffer != NULL) {
                    memcpy(buffer, &val, 4);
                    buffer += 4;  
                }
            } else if (*c == 'l') {
                double val = va_arg(args, double);
                num_of_bytes += 8;

                if (buffer != NULL) {
                    memcpy(buffer, &val, 8);
                    buffer += 8;
                }
            } else {
                char *str = va_arg(args, char *);
                int len = (int)strlen(str) + 1;
                num_of_bytes += len;

                if (buffer != NULL) {
                    memcpy(buffer, str, len);
                    buffer += len;
                }
            }
        }
    }

    va_end(args);
    return num_of_bytes;
}