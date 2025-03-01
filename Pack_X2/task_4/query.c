#include <ctype.h>
#include <stdint.h>

extern int N;

int64_t Sum(int l, int r);

int Query(int l, int64_t sum) {
    int left = l;
    int right = N+1;

    while (left < right) {
        int mid = (left + right) / 2;
        int64_t curr_sum = Sum(l, mid);
        if (curr_sum <= sum) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left - 1;
}