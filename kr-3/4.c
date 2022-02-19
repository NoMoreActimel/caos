#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>


bool overflow_check(uint16_t float_value) {
    for (int i = 10; i != 15; ++i) {
        if (!((float_value >> i) & 1)) {
            return false;
        }
    }
    return true;
}

int16_t f_exp(uint16_t f) {
    f <<= 1;
    f >>= 11;
    return f;
}

uint16_t f_man(uint16_t f) {
    f <<= 6;
    f >>= 6;
    return f;
}


uint16_t sat_mul4_half(uint16_t f) {
    if (overflow_check(f)) {
        return f;
    }

    uint16_t exp = f_exp(f);
    uint16_t man = f_man(f);

    if (exp == 0) {
        if (man == 0) {
            return f;
        } else {
            if (man >= (1 << 9)) {
                man -= 1 << 9;
                return ((f >> 15) << 15) + (2 << 10) + (man << 1); 
            } else if (man >= (1 << 8)) {
                man -= 1 << 8;
                return ((f >> 15) << 15) + (1 << 10) + (man << 2);
            } else {
                return ((f >> 15) << 15) + (man << 2);
            }
        }
    } else if (exp < 29) {
        return ((f >> 15) << 15) + ((exp + 2) << 10) + man;
    }

    exp = 30;
    return (exp << 10) + 1023 + ((f >> 15) << 15);
}

// 2^(-14) * 0.1 -> 2^(-13)
// 0 00000 1000000000 -> 0 00010 0000000000

// 2^(-14) * 0.01 -> 2^(-14)
// 0 00000 0100000000 -> 0 00001 0000000000

// 2^(-14) * 0.11 -> 1.5 * 2^(-13)
// 0 00000 1100000000 -> 0 00010 1000000000

// 2^(-14) * 0.101 -> 1.25 * 2^(-13)
// 0 00000 1010000000 -> 0 00010 0100000000

// 2^(-14) * 0.011 -> 1.5 * 2^(-14)
// 0 00000 0110000000 -> 0 00001 1000000000

// 2^(-14) * 0.001 -> 2^(-15)
// 0 00000 0010000000 -> 0 00000 1000000000

/*
void bitwise_float_print(uint16_t f) {
    printf("%d ", (f >> 15));

    for (int i = 14; i != 9; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf(" ");

    for (int i = 9; i != -1; --i) {
        printf("%d", (f >> i) & 1);
    }
    printf("\n");
}

int main() {
    uint16_t f = (1 << 7);
    uint16_t res = sat_mul4_half(f);
    bitwise_float_print(f);
    bitwise_float_print(res);
}*/