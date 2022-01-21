#include <stdio.h>
#include <stdlib.h>

struct data {
    int (*get_rank)(const struct data*);
    char secret[];
};


int compare(const void *element1, const void *element2) {
    return (void (*)(void *))(element1)() <  (void (*)(void *))(element2)();
}

void rank_sort(struct data* elements[], size_t size) {
    qsort(elements, size, 4, compare);
}
