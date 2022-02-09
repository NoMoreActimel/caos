#include "4_func.c"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

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

    a = -9223372036854775808;
    b = 1;

    int64_t* res = malloc(sizeof(int64_t));

    printf("OF: %d\n", imull_overflow(a, b, res));
    printf("a*b = %lld\n", *res);
    
    printf("a:   ");
    bitwise_print(a);
    printf("b:   ");
    bitwise_print(b);
    printf("a*b: ");
    bitwise_print(*res);

    printf("\nBuiltin Function Answer:\n");
    printf("OF: %d\n", __builtin_smul_overflow(a, b, res));
    printf("a+b = %lld\n", *res);
    
    printf("a:   ");
    bitwise_print(a);
    printf("b:   ");
    bitwise_print(b);
    printf("a*b: ");
    bitwise_print(*res);


    free(res);
}