// #include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void tinyconv(uint8_t bytes[], size_t size) {
    for (size_t i = 0; i != size; ++i) {
        for (int j = 0; j != 4; ++j) {
            bool x = (bytes[i] >> j) & 1;
            bool y = (bytes[i] >> (7 - j)) & 1;

            bytes[i] -= x << j;
            bytes[i] -= y << (7 - j);
            bytes[i] += y << j;
            bytes[i] += x << (7 - j);
        }
    }
}
/*

void bitwise_print(int8_t a) {
    for (int i = 7; i != -1; --i) {
        printf("%d", (a >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    uint8_t b[] = {0xfa, 0x04};
    bitwise_print(b[0]);
    bitwise_print(b[1]);
    tinyconv(b, 2);
    bitwise_print(b[0]);
    bitwise_print(b[1]);
    // теперь b == {0x5f, 0x20}
}*/