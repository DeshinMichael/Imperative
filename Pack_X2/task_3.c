#include <stdio.h>

int main() {
    
#if (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)
    printf("Compiler: GCC\n");
#elif defined(__clang__)
    printf("Compiler: clang\n");
#elif defined(__TINYC__)
    printf("Compiler: TCC\n");
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
    printf("Bitness: 64\n");
#elif defined(__i386__) || defined(_M_IX86)
    printf("Bitness: 32\n");
#endif

#ifdef NDEBUG
    printf("Asserts: disabled\n");
#else
    printf("Asserts: enabled\n");
#endif

    return 0;
}