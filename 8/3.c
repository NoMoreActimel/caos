#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

union ufloat {
    float f;
    uint32_t u;
};

// value - посмотреть расположение битов в зависимости от старшей 1
// расстояние от старшей 1 = расстояние от левого края мантиссы
// то есть для 2^20 + 2^3 расстояние от левого края мантиссы = 16 
// если это расстояние >= 23 для какого-то единичного бита, то точным образом число не представимо
// то есть если maxbit - i > 23, то неточно


bool no_integer_rounding(uint32_t value) {
    int max_bit = 0;

    for (int i = 31; i != -1; --i) {
        if ((value >> i) & 1) {
            max_bit = i;
            break;
        }
    }

    for (int i = 0; i < max_bit - 23; ++i) {
        if ((value >> i) & 1) {
            return false;
        }
    }
    return true;
}

int main() {
    uint32_t x;
    while (scanf("%u", &x) == 1) {
        printf("%d\n", no_integer_rounding(x));
    }
}