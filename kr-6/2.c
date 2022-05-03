#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

enum Constants {EXP_IND = 23, SIGN_IND = 31};

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

    for (int i = SIGN_IND; i != -1; --i) {
        if ((value >> i) & 1) {
            max_bit = i;
            break;
        }
    }

    for (int i = 0; i < max_bit - EXP_IND; ++i) {
        if ((value >> i) & 1) {
            return false;
        }
    }
    return true;
}

void myfloorf(float *arg) {
    union ufloat uf;
    uf.f = *arg;

    printf("%d\n", uf.u);

    while (no_integer_rounding(uf.u)) {
        uf.u--;
    }

    printf("%d\n", uf.u);

    *arg = uf.f;
}

// 1 11111111 11111111111111111111111

int main() {
    float f = 1.5;
    myfloorf(&f);
    printf("%f\n", f);
}