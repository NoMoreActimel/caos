#include <stdbool.h>
#include <stdint.h>


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

    uint16_t exp = f_exp(f) + 15;
    if (exp < 29) {
        return ((exp + 2) << 10) + f_man(f) + ((f >> 15) << 15);
    }

    exp = 30;
    return (exp << 10) + 1023 + ((f >> 15) << 15);
}   

//  exp max = 31 
