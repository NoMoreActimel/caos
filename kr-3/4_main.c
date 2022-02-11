#include "4.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t sat_mul4_half(uint16_t f);

int main() {
    uint16_t f = 1.0;
    printf("%hu\n", sat_mul4_half(f));
}