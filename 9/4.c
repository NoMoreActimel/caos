#include <stdio.h>
#include <stdlib.h>

void dot_product(int, const float*, const float*, float*);

int main() {
    int n = 5;
    float* x = malloc(n * sizeof(float));
    float* y = malloc(n * sizeof(float));
    float* res = malloc(sizeof(float));

    dot_product(n, x, y, res);

    printf("%f\n", *res);
}