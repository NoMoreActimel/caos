#include <stdio.h>
#include <stdlib.h>

void discrim(float, float, float, float*);

int main() {
    float a = 3.0;
    float b = 3.0;
    float c = 1.0;
    float* res = malloc(sizeof(float));

    discrim(a, b, c, res);    

    printf("%f\n", *res);
    free(res);
}