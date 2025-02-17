#include <stdio.h>
#include <string.h>

typedef long long ll;

ll add(ll num1, ll num2) {
    return num1 + num2;
}

ll sub(ll num1, ll num2) {
    return num1 - num2;
}

ll mul(ll num1, ll num2) {
    return num1 * num2;
}

ll operate(char* argv[], int index, ll num1, ll num2, ll (*operation)(ll, ll)) {
    sscanf(argv[index+1], "%lld", &num1);
    sscanf(argv[index+2], "%lld", &num2);
    return operation(num1, num2);
}

int main(int argc, char* argv[]) {
    ll num1, num2, res = 0, mod = 0;

    if (argc == 1) {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }

    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-m")) {
            sscanf(argv[i+1], "%lld", &mod);
            i += 1;
        } else {
            if (0 == strcmp(argv[i], "add")) {
                res = operate(argv, i, num1, num2, add);
            } else if (0 == strcmp(argv[i], "sub")) {
                res = operate(argv, i, num1, num2, sub);
            } else if (0 == strcmp(argv[i], "mul")) {
                res = operate(argv, i, num1, num2, mul);
            }
            i += 2;
        }
    }

    if (mod != 0) {
        res = (res % mod + mod) % mod;
    }

    printf("%lld", res);
    
    return 0;
}