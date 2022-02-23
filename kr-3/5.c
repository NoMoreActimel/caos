#include <stdbool.h>
#include <stdint.h>

enum Constatns {
    F32_EXPIND = 23,
    F32_SIGNIND = 31,
    F32_MAXEXP = 255,
    F32_EXPBIAS= 127,
    F16_EXPIND = 10,
    F16_SIGNIND = 15,
    F16_MAXEXP = 31,
    F16_EXPBIAS = 15
};

union ufloat {
    float f;
    uint32_t u;
};

bool ith_bit(uint32_t x, int i) {
    return (x >> i) & 1;
}

bool overflow_check(uint32_t float_value) {
    for (int i = F32_EXPIND; i != F32_SIGNIND; ++i) {
        if (!((float_value >> i) & 1)) {
            return false;
        }
    }
    return true;
}
bool short_overflow_check(uint16_t float_value) {
    for (int i = F16_EXPIND; i != F16_SIGNIND; ++i) {
        if (!((float_value >> i) & 1)) {
            return false;
        }
    }
    return true;
}

bool f_sign(uint32_t f) {
    return f >> F32_SIGNIND;
}
bool short_f_sign(uint16_t f) {
    return f >> F16_SIGNIND;
}

int32_t f_exp(uint32_t f) {
    return (f << 1) >> (F32_EXPIND + 1);
}
int16_t short_f_exp(uint16_t f) {
    return (f << 1) >> (F16_EXPIND + 1);
}

uint32_t f_man(uint32_t f) {
    return (f << (32 - F32_EXPIND)) >> (32 - F32_EXPIND);
}
uint16_t short_f_man(uint16_t f) {
    return (f << (16 - F16_EXPIND)) >> (16 - F16_EXPIND);
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

uint16_t short_inf(bool sign) {
    return ((1 & sign) << F16_SIGNIND) + (F16_MAXEXP << F16_EXPIND);
}

uint16_t short_nan(bool sign) {
    return ((1 & sign) << F16_SIGNIND) + (F16_MAXEXP << F16_EXPIND) + 1;
}


uint16_t float_to_fp16(float f) {
    union ufloat F;
    F.f = f;
    uint16_t f_short = 0;

    bool sign = f_sign(F.u);
    uint32_t exp = f_exp(F.u);
    uint32_t man = f_man(F.u);

    if (exp == F32_MAXEXP && man) {
        return short_nan(sign);
    }
    if (exp == F32_MAXEXP) {
        return short_inf(sign);
    }

    // доделать со смещением exp, которое неучтено

    if (exp - F32_EXPBIAS >= F16_MAXEXP - F16_EXPBIAS) {
        return short_inf(sign);
    }

    f_short += sign << F16_SIGNIND;
    f_short += (exp - F32_EXPBIAS + F16_EXPBIAS) << F16_EXPIND;

    uint16_t short_man = man >> (F32_EXPIND - F16_EXPIND);
    uint32_t rounding_edge = 1 << (F32_EXPIND - F16_EXPIND - 1);
    uint32_t man_remainder = man - ((uint32_t)(short_man) << (F32_EXPIND - F16_EXPIND));
    if (man_remainder > rounding_edge) {
        short_man++;
    } else if (man_remainder == rounding_edge) {
        if (ith_bit(short_man, 0)) {
            short_man++;
        }
    }

    f_short += short_man;
    return f_short;
}
