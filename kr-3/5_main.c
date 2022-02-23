#include <stdio.h>
#include "5.c"

void bitwise_float_print(uint32_t f) {
    printf("%d ", (f >> F32_SIGNIND));

    for (int i = F32_SIGNIND - 1; i != F32_EXPIND - 1; --i) {
        printf("%d", ith_bit(f, i));
    }
    printf(" ");

    for (int i = F32_EXPIND - 1; i != -1; --i) {
        printf("%d", ith_bit(f, i));
    }
    printf("\n");
}
void bitwise_short_float_print(uint16_t f) {
    printf("%d ", (f >> F16_SIGNIND));

    for (int i = F16_SIGNIND - 1; i != F16_EXPIND - 1; --i) {
        printf("%d", ith_bit(f, i));
    }
    printf(" ");

    for (int i = F16_EXPIND - 1; i != -1; --i) {
        printf("%d", ith_bit(f, i));
    }
    printf("\n");
}

int main() {
    union ufloat F;
    F.f = 1.9990234375;
    uint16_t res = float_to_fp16(F.f);
    bitwise_float_print(F.u);
    bitwise_short_float_print(res);
    printf("%x\n", res);
}