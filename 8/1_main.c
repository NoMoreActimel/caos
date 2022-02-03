#include "1.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    union ufloat value_bits = { .u = 0x80500000 };
    int* value_sign = malloc(sizeof(int));
    FPClass classificator = fpclassf(value_bits.f, value_sign);

    printf("%d %d\n", classificator, *value_sign);
    free(value_sign);
}