#include <stdio.h>
#include <stdint.h>

enum CPUID_Constants {
    EXT_FAMILY_IND = 20,
    EXT_FAMILY_SIZE = 8,
    EXT_MODEL_IND = 16,
    EXT_MODEL_SIZE = 4,
    FAMILY_IND = 8,
    FAMILY_SIZE = 4,
    MODEL_IND = 4,
    MODEL_SIZE = 4
    };

int main() {
    uint32_t a, b, c, d;

    asm ( "mov $1, %%eax\n\t"
          "cpuid\n\t"
          //"mov %%eax, %0\n\t"
          //"mov %%ecx, %1\n\t"
          //"mov %%edx, %2\n\t"
          : "=a"(a), "=b"(b), "=c"(c), "=d"(d));

    uint32_t family = (a << (32 - FAMILY_IND - FAMILY_SIZE)) >> (32 - FAMILY_SIZE);
    uint32_t model = (a << (32 - MODEL_IND - MODEL_SIZE)) >> (32 - MODEL_SIZE);

    
    if (family == 6 || family == 15) {
        model += (a << (32 - EXT_MODEL_IND - EXT_MODEL_SIZE)) >> (32 - EXT_MODEL_SIZE - MODEL_SIZE);
    }
    if (family == 15) {
        family += (a << (32 - EXT_FAMILY_IND - EXT_MODEL_SIZE)) >> (32 - EXT_FAMILY_SIZE);
    }

    printf("family=%d model=%d ecx=0x%x edx=0x%x\n", family, model, c, d);
}