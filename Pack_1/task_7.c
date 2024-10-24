#include <stdio.h>

int main() {
    int n, l_n, p_n; // n, этаж квартиры n, подъезд квартиры n
    int m, p, k, l; // другая квартира, подъезд, этаж, этажей в доме
    
    scanf("%d", &n);
    scanf("%d %d %d %d", &m, &p, &k, &l);

    int k_on_level = m / ((p - 1) * l + (k - 1)); // количество квартир на этаже
    int k_in_p = k_on_level * l; // количество квартир в подъезде

    if (n % k_in_p == 0) { // поиск подъезда квартиры n
        p_n = n / k_in_p;
    } else {
        p_n = n / k_in_p + 1;
    }

    int k_in_p_n = n - l * k_on_level * (p_n - 1); // количество квартир в подъезде квартиры n

    if (k_in_p_n % k_on_level == 0) { // поиск этажа квартиры n
        l_n = k_in_p_n / k_on_level;
    } else {
        l_n = k_in_p_n / k_on_level + 1;
    }
    
    printf("%d %d", p_n, l_n);

    return 0;
}