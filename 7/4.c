#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool ith_bit(uint64_t a, int i) {
    return (a >> i) & 1;
}

uint64_t add_ull(uint64_t a, uint64_t b) {
    uint64_t c = 0;

    for (int i = 0; i != 63; ++i) {
        if (ith_bit(a, i)) {
            c += 1ull << i;
        }
        if (ith_bit(b, i)) {
            c += 1ull << i;
        }
    }
    
    bool a_63 = ith_bit(a, 63);
    bool b_63 = ith_bit(b, 63);

    if (ith_bit(c, 63)) {
        if ((a_63 && !b_63) || (!a_63 && b_63)) {
            c -= 1ull << 63;
        }
    } else {
        if ((a_63 && !b_63) || (!a_63 && b_63)) {
            c += 1ull << 63;
        }
    }

    return c; 
}

void overflowed_mull(uint64_t a, uint64_t b, bool sign, uint64_t *res) {
    *res = 0;
    for (int i = 0; i != 64; ++i) {
        if (ith_bit(a, i)) {
            for (int j = 0; j != 64; ++j) {
                if (ith_bit(b, j)) {
                    //*res = add_ull(*res, 1ull << (i + j));
                    if (i + j > 63) {
                        continue;
                    }
                    *res += 1ull << (i + j);
                }
            }
        }
    }

    if (sign) {
        for (int i = 0; i != 63; ++i) {
            *res = UINT64_MAX - *res;
        }
    }
}

int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    if (a == 0 || b == 0) {
        *res = 0;
        return 0;
    }

    bool sign = 0; // positive
    bool overflow = false;

    if (a == - INT64_MAX - 1) {
        if (b == 1) {
            *res = a;
            return 0;
        } else {
            overflow = true;
        }
        sign = !sign;
    } else if (a < 0) {
        sign = !sign;
        a = -a;
    }

    if (b == - INT64_MAX - 1) {
        if (a == 1) {
            *res = b;
            return 0;
        } else {
            overflow = true;
        }
    } else if (b < 0) {
        sign = !sign;
        b = -b;
    }

    if (INT64_MAX / a < b) {
        overflow = true;
    }


    if (overflow) {
        overflowed_mull(a, b, sign, res);
        return 1;
    } else {
        if (sign) {
            *res = -a * b;
        } else {
            *res = a * b;
        }
        return 0;
    }
}

void bitwise_print(int64_t a) {
    for (int i = 63; i != -1; --i) {
        printf("%d", ith_bit(a, i));
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    FILE* in = fopen("input.txt", "r");
    int64_t a, b;
    // fscanf(in, "%" SCNd64 "%" SCNd64, &a, &b);
    a = -(1ll << 62);
    b = -1;

    int64_t* res = malloc(sizeof(int64_t));

    printf("OF: %d\n", imull_overflow(a, b, res));
    printf("a+b = %lld\n", *res);
    
    printf("a:   ");
    bitwise_print(a);
    printf("b:   ");
    bitwise_print(b);
    printf("a+b: ");
    bitwise_print(*res);

    free(res);
}