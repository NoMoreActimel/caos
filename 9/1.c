#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t a, b, c, d;

    asm ( "mov $1, %%eax\n\t"
          "cpuid\n\t"
          //"mov %%eax, %0\n\t"
          //"mov %%ecx, %1\n\t"
          //"mov %%edx, %2\n\t"
          : "=a"(a), "=b"(b), "=c"(c), "=d"(d));

    uint32_t family = (a << 20) >> 28;
    uint32_t model = (a << 24) >> 28;

    
    if (family == 6 || family == 15) {
        model += (a << 12) >> 24;
    }
    if (family == 6) {
        family += (a << 4) >> 25;
    }

    printf("family=%d model=%d ecx=0x%x edx=0x%x\n", family, model, c, d);
}