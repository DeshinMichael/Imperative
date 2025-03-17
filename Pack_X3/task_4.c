#include <stdio.h>
#include <math.h>

#define N 1024

double integral_expr(double t, double l, double cx[4], double cy[4], double cz[4]) {
    double dx = cx[1] + 2 * cx[2] * (t-l) + 3 * cx[3] * (t-l) * (t-l);
    double dy = cy[1] + 2 * cy[2] * (t-l) + 3 * cy[3] * (t-l) * (t-l);
    double dz = cz[1] + 2 * cz[2] * (t-l) + 3 * cz[3] * (t-l) * (t-l);

    return sqrt(dx * dx + dy * dy + dz * dz);
}

double integration_simpson(double l, double r, double cx[4], double cy[4], double cz[4]) {
    double h = (r - l) / N;
    double sum = 0.0;

    sum += integral_expr(l, l, cx, cy, cz);
    sum += integral_expr(r, l, cx, cy, cz);

    for (int i = 1; i < N; i++) {
        double t = l + i * h;
        if (i % 2 == 0) {
            sum += 2.0 * integral_expr(t, l, cx, cy, cz);
        } else {
            sum += 4.0 * integral_expr(t, l, cx, cy, cz);
        }
    }

    sum *= (h / 3.0);
    return sum;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    double span_len, total_len = 0.0;
    double l, r;
    double cx[4], cy[4], cz[4];

    while (n--) {
        scanf("%lf %lf", &l, &r);

        scanf("%lf %lf %lf %lf", &cx[0], &cx[1], &cx[2], &cx[3]);
        scanf("%lf %lf %lf %lf", &cy[0], &cy[1], &cy[2], &cy[3]);
        scanf("%lf %lf %lf %lf", &cz[0], &cz[1], &cz[2], &cz[3]);

        span_len = integration_simpson(l, r, cx, cy, cz);
        total_len += span_len;
    }

    printf("%.20f", total_len);

    return 0;
}