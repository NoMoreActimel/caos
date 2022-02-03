// #pragma once
// #include "1.h"
#include <stdbool.h>
#include <stdint.h>

union ufloat {
    float f;
    uint32_t u;
};

bool overflow_check(uint32_t float_value) {
    for (int i = 23; i != 31; ++i) {
        if (!((float_value >> i) & 1)) {
            return false;
        }
    }
    return true;
}

bool nan_check(uint32_t float_value) {
    for (int i = 0; i != 23; ++i) {
        if ((float_value >> i) & 1) {
            return true;
        }
    }
    return false;
}

bool denormalized_check(uint32_t float_value) {
    for (int i = 23; i != 31; ++i) {
        if ((float_value >> i) & 1) {
            return false;
        }
    }
    return true;
}


FPClass fpclassf(float value, int *psign) {
    union ufloat value_bits = {.f = value };
    FPClass value_type;
    *psign = value_bits.u >> 31;

    if (value == 0) {
        value_type = FFP_ZERO;
    } else if (overflow_check(value_bits.u)) {
        if (nan_check(value_bits.u)) {
            value_type = FFP_NAN;
            *psign = 0;
        } else {
            value_type = FFP_INF;
        }
    } else if (denormalized_check(value_bits.u)) {
        value_type = FFP_DENORMALIZED;
    } else {
        value_type = FFP_NORMALIZED;
    }

    return value_type;
}