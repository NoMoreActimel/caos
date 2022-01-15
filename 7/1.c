#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t a, int32_t b) {
    uint32_t ua = (uint32_t)a;
    uint32_t ub = (uint32_t)b;
    uint32_t uc = ua + ub;

    if (ua < (1ul << 31) && ub < (1ul << 31)) {
        if (uc >= (1ul << 31)) {
            return (int32_t)((1ul << 31) - 1);
        } else {
            return (int32_t)uc;
        }
    } else if (ua >= (1ul << 31) && ub >= (1ul << 31)) {
        if (uc < (1ul << 31)) {
            return (int32_t)((1ul << 31));
        } else {
            return (int32_t)uc;
        }
    } else {
        return (int32_t)uc;
    }
}
/*
int main() {
    int32_t a, b;
    scanf("%d%d", &a, &b);
    satsum(a, b);
    printf("%d\n", satsum(a, b));
}
*/