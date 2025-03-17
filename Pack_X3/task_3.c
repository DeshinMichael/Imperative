#include <stdio.h>
#include <ctype.h>

static double tokens[500001];
static int k_tok = 0;
static int pos = 0;

int read_token() {
    if (pos < k_tok) {
        return tokens[pos++];
    }
    return -1;
}

int peek_token() {
    if (pos < k_tok) {
        return tokens[pos];
    }
    return -1;
}

double operate(double a, double b, char oper) {
    double res = 0.0;

    switch (oper) {
        case '+': 
            res = a + b; 
            break;
        case '-': 
            res = a - b; 
            break;
        case '*':  
            res = a * b; 
            break;
        case '/': 
            res = a / b; 
            break;
    }
    return res;
}

double parse_expr();

double parse_atom() {
    int t = peek_token();

    if (t == -1) {
        return 0.0;
    } else if (t >= 256) {
        return (double)(read_token() - 256);
    } else {
        if (t == '-') {
            read_token();
            return -parse_atom();
        }
    
        if (t == '(') {
            read_token();
            double res = parse_expr();
            read_token();
            return res;
        }
    }
}

double parse_monome() {
    double res = parse_atom();

    while (1) {
        int t = peek_token();
        if (t == '*' || t == '/') {
            char oper = read_token();
            double val = parse_atom();
            res = operate(res, val, oper);
        } else {
            break;
        }
    }
    return res;
}

double parse_expr() {
    double res = parse_monome();

    while (1) {
        int t = peek_token();
        if (t == '+' || t == '-') {
            char oper = read_token();
            double val = parse_monome();
            res = operate(res, val, oper);
        } else {
            break;
        }
    }
    return res;
}

void stdin_to_tokens() {
    while (1) {
        int c = getchar();

        if (c == EOF) {
            tokens[k_tok++] = -1;
            break;
        }
        if (isspace(c)) {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            tokens[k_tok++] = c;
        }
        if (isdigit(c)) {
            int num = c - '0';
            while (1) {
                int next = getchar();
                if (next == EOF) {
                    break;
                }
                if (!isdigit(next)) {
                    ungetc(next, stdin);
                    break;
                }
                num = num * 10 + (next - '0');
            }
            tokens[k_tok++] = num + 256;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    stdin_to_tokens();

    double res = parse_expr();

    printf("%.20f\n", res);

    return 0;
}