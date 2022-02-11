#include <stdio.h>
#include <stdlib.h>

void myexp(double, double*);

int main() {
    double x = 0.5;
    double* res = malloc(sizeof(double));

    myexp(x, res);
    printf("%f\n", *res);
}