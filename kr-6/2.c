#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

enum Constants {EXP_IND = 23, SIGN_IND = 31};

// x = s * ((2^(23) + m) * 2^(-23)) * 2^(e - 127)
// p = e - 127
// |x| = (1 + (m >> 23)) << p
// |x| = ((1 << 23) + m) << (e - 150)
// |x| = (1 << (e - 127)) + sum m[i] << (e + i - 150)
// e < 127 ? e_r = 0 : e_r = e
// e_r = 0 ? m_r = 0 : m_r[i] = m[i] while e + i - 150 >= 0

union ufloat {
    float f;
    uint32_t u;
};

bool ith_bit(uint32_t x, int i) {
    return (x >> i) & 1;
}

void bitwise_print(uint32_t x) {
    for (int i = 31; i != -1; --i) {
        printf("%d", ith_bit(x, i));
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void myfloorf(float *arg) {
    union ufloat uf;
    uf.f = *arg;

    int32_t e = (uf.u << 1) >> (EXP_IND + 1);
    int32_t m = (uf.u << (32 - EXP_IND)) >> (32 - EXP_IND);
    // printf("value = %d:\n", uf.u);
    // bitwise_print(uf.u);
    // printf("e = %d:\n", e);
    // bitwise_print(e);
    // printf("m = %d:\n", m);
    // bitwise_print(m);

    union ufloat uf_rounded;
    if (e < 127) {
        uf_rounded.u = 0;
        *arg = uf_rounded.f;
        return;
    } else if (e >= 150) {
        return;
    }

    uf_rounded.u = (uf.u >> EXP_IND) << EXP_IND;
    for (int i = 150 - e; i < EXP_IND; ++i) {
        if (ith_bit(m, i)) {
            // printf("%d\n", e + i - 150);
            uf_rounded.u += (1 << i);
        }
    }

    // printf("rounded = %d:\n", uf_rounded.u);
    // bitwise_print(uf_rounded.u);    

    *arg = uf_rounded.f;
}

/*
int main() {
    float f = 1.5;
    myfloorf(&f);
    printf("%f\n", f);
}*/