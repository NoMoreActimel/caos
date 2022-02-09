#include <stdio.h>
#include <stdlib.h>

void myhypot(double, double, double*);

int main() {
    double x = 3.0;
    double y = 4.0;
    double* res = malloc(sizeof(double));
    myhypot(x, y, res);
    
    printf("%f\n", *res);
    free(res);
}