#include <inttypes.h>
#include <stdbool.h>

bool ith_bit(uint64_t a, int i) {
    return (a >> i) & 1;
}

uint64_t overflowed_mull(uint64_t a, uint64_t b) {
    uint64_t c = 0;
    for (int i = 0; i != 64; ++i) {
        if (ith_bit(a, i)) {
            for (int j = 0; j != 64; ++j) {
                if (ith_bit(b, j)) {
                    if (i + j > 63) {
                        continue;
                    }
                    c += 1ull << (i + j);
                }
            }
        }
    }

    return c;
}

uint64_t make_signed(uint64_t a, bool sign) {
    if (sign) {
        return UINT64_MAX ^ (a - 1);
    } else {
        return a;
    }
}

int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    if (a == 0 || b == 0) {
        *res = 0;
        return 0;
    }

    if (a < b) {
        int64_t c = a;
        a = b;
        b = c;
    }
    // a >= b now

    uint64_t ua = a, ub = b;
    bool sign = 0; // positive
    bool overflow = false;

    if (a == INT64_MIN) { // a >= b -> a = b = INT64_MIN
        *res = 0;
        return 1;
    }
    
    if (a < 0) {
        sign = !sign;
        ua = -a;
    }

    if (b == INT64_MIN) {
        sign = !sign;
        if (a == 1) {
            *res = b;
            return 0;
        } else {
            *res = make_signed(overflowed_mull(ua, ub), sign);
            return 1;
        }
    } else if (b < 0) {
        sign = !sign;
        ub = -b;
    }

    if (!overflow) {
        if (sign && ua * ub == (uint64_t)(INT64_MIN)) {
            *res = INT64_MIN;
            return 0;
        }
        if ((uint64_t)INT64_MAX / ua < ub) {
            overflow = true;
        }
    }

    if (overflow) {
        *res = make_signed(overflowed_mull(ua, ub), sign);
        return 1;
    } else {
        *res = make_signed(ua * ub, sign);
        return 0;
    }
}
