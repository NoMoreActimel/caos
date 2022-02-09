#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef double (*funcptr_t)(double);


typedef struct FunctionTable {
    char* name;
    funcptr_t func;
} FunctionTable;



const static FunctionTable functions [] = {
    {"sin", sin},
    {"cos", cos},
    {"exp", exp},
    {"log", log},
    {"tan", tan},
    {"sqrt", sqrt}
};


int main() {
    double x = 0;
    char* name = NULL;

    while (scanf("%ms %lf", &name, &x) == 2) {
        int func_ind = -1;;
        for (int i = 0; i != sizeof(functions) / sizeof(FunctionTable); ++i) {
            if (strcmp(functions[i].name, name) == 0) {
                func_ind = i;
                break;
            }
        }

        if (func_ind == -1) {
            printf("nan\n");
        } else {
            printf("%a\n", functions[func_ind].func(x));
        }
        free(name);
    }

}