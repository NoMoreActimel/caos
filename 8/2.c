#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

enum Constants {exp_ind = 23, sign_ind = 31};

bool sign(uint32_t float_value) {
    return (float_value >> sign_ind) & 1;
}

uint32_t exponent_bits(uint32_t float_value) {
    uint32_t exp = 0;
    for (int i = exp_ind; i != sign_ind; ++i) {
        if ((float_value >> i) & 1) {
            exp += 1 << (i - exp_ind);
        }
    }
    return exp;
}

uint32_t mantissa_bits(uint32_t float_value) {
    uint32_t mantissa = 0;
    for (int i = 0; i != exp_ind; ++i) {
        if ((float_value >> i) & 1) {
            mantissa += 1 << i;
        }
    }
    return mantissa;
}

union ufloat {
    float f;
    uint32_t u;
};


int main() {
    union ufloat value_bits;

    while (scanf("%f", &value_bits.f) == 1) {
        printf("%d %d %x\n", sign(value_bits.u), exponent_bits(value_bits.u), mantissa_bits(value_bits.u));
    }
}