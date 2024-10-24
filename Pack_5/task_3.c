#include <stdio.h>
#include <stdlib.h>

#define SIZE(n) (2 * (n) + 1)

typedef struct RingBuffer {
    int *arr;
    int beg;
    int end;
    int counter;
    int cap;
} RingBuffer;

void init(RingBuffer *buf, int size) {
    buf->arr = (int *) malloc(size * sizeof(int));
    buf->beg = 0;
    buf->end = 0;
    buf->counter = 0;
    buf->cap = size;
}

void push_end(RingBuffer *buf, int val) {
    buf->arr[buf->end] = val;
    buf->end = (buf->end + 1) % buf->cap;
    buf->counter++;
}

void push_beg(RingBuffer *buf, int val) {
    buf->beg = (buf->beg - 1 + buf->cap) % buf->cap;
    buf->arr[buf->beg] = val;
    buf->counter++;
}

int pop_end(RingBuffer *buf) {
    if (buf->counter == 0) return 0;
    buf->end = (buf->end - 1 + buf->cap) % buf->cap;
    buf->counter--;
    return buf->arr[buf->end];
}

int pop_beg(RingBuffer *buf) {
    if (buf->counter == 0) return 0;
    int card = buf->arr[buf->beg];
    buf->beg = (buf->beg + 1) % buf->cap;
    buf->counter--;
    return card;
}

void free_buf(RingBuffer *buf) {
    free(buf->arr);
}

void print_buf(RingBuffer *buf) {
    printf("%d ", buf->counter);
    for (int i = 0; i < buf->counter; i++) {
        printf("%d ", buf->arr[(buf->beg + i) % buf->cap]);
    }
    printf("\n");
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    RingBuffer left_buf, right_buf;
    init(&left_buf, SIZE(n));
    init(&right_buf, SIZE(n));

    for (int i = 1; i <= n; i++) {
        push_end(&left_buf, i);
        push_end(&right_buf, -i);
    }

    char oper;
    scanf("%c", &oper);
    for (int i = 0; i < m; i++) {
        scanf("%c", &oper);
        int operation = oper >= 'A' ? oper - 'A' + 10 : oper - '0';

        int from_right = (operation & 8) != 0;
        int from_bottom = (operation & 4) != 0;
        int to_right = (operation & 2) != 0;
        int to_bottom = (operation & 1) != 0;

        int card = from_right ? (from_bottom ? pop_end(&right_buf) : pop_beg(&right_buf)) : (from_bottom ? pop_end(&left_buf) : pop_beg(&left_buf));

        if (card != 0) {
            if (to_right) {
                to_bottom ? push_end(&right_buf, card) : push_beg(&right_buf, card);
            } else {
                to_bottom ? push_end(&left_buf, card) : push_beg(&left_buf, card);
            }
        }
    }

    print_buf(&left_buf);
    print_buf(&right_buf);

    free_buf(&left_buf);
    free_buf(&right_buf);

    return 0;
}