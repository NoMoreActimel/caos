#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t a, int32_t b) {
    int32_t int_max = ((1u << 31) - 1);
    int32_t int_min = ((1u << 31));
    int32_t c;

    if (__builtin_add_overflow(a, b, &c)) {
        if (a > 0) {
            return int_max;
        }
        return int_min;
    }
    return c;
}
/*
int main() {
    int32_t a, b;
    scanf("%d%d", &a, &b);
    satsum(a, b);
    printf("%d\n", satsum(a, b));
}*/