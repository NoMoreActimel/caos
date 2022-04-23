#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>

enum { 
    MAN_SZ = 10,
    EXP_SZ = 5,
    SIGN_SZ = 1,
    MAX_EXP = 30,
    MAX_MAN = 1023
};


bool overflow_check(uint16_t float_value) {
    for (int i = MAN_SZ; i != MAN_SZ + EXP_SZ; ++i) {
        if (!((float_value >> i) & 1)) {
            return false;
        }
    }
    return true;
}

int16_t f_exp(uint16_t f) {
    f <<= SIGN_SZ;
    f >>= MAN_SZ + SIGN_SZ;
    return f;
}

uint16_t f_man(uint16_t f) {
    f <<= EXP_SZ + SIGN_SZ;
    f >>= EXP_SZ + SIGN_SZ;
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
            if (man >= (1 << (MAN_SZ - 1))) {
                man -= 1 << (MAN_SZ - 1);
                return ((f >> (MAN_SZ + EXP_SZ)) << (MAN_SZ + EXP_SZ)) + (2 << MAN_SZ) + (man << 1); 
            } else if (man >= (1 << (MAN_SZ - 2))) {
                man -= 1 << (MAN_SZ - 2);
                return ((f >> (MAN_SZ + EXP_SZ)) << (MAN_SZ + EXP_SZ)) + (1 << MAN_SZ) + (man << 2);
            } else {
                return ((f >> (MAN_SZ + EXP_SZ)) << (MAN_SZ + EXP_SZ)) + (man << 2);
            }
        }
    } else if (exp < MAX_EXP - 1) {
        return ((f >> (MAN_SZ + EXP_SZ)) << (MAN_SZ + EXP_SZ)) + ((exp + 2) << MAN_SZ) + man;
    }

    exp = MAX_EXP;
    return (exp << MAN_SZ) + MAX_MAN + ((f >> (MAN_SZ + EXP_SZ)) << (MAN_SZ + EXP_SZ));
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