#include <stdio.h>
#include <stdlib.h>

void dot_product(int, const float*, const float*, float*);

int main() {
    int n = 8;
    float* x = malloc(n * sizeof(float));
    float* y = malloc(n * sizeof(float));
    float* res = malloc(sizeof(float));

    x[0] = 1.5;
    x[1] = 3.5;
    x[2] = 1.5;
    x[3] = 3.5;
    x[4] = 1.5;
    x[5] = 3.5;
    x[6] = 1.5;
    x[7] = 3.5;

    y[0] = -3.5;
    y[1] = 1.0;
    y[2] = -3.5;
    y[3] = 1.0;
    y[4] = -3.5;
    y[5] = 1.0;
    y[6] = -3.5;
    y[7] = 1.0;

    dot_product(n, x, y, res);
    printf("%f\n", *res);

    free(x);
    free(y);
    free(res);
}