#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int (*get_rank)(const struct data*);
    // int a;
    char secret[];
} data;

int compare (const void* element1, const void* element2) {
    return (*(data**)element1)->get_rank(*(data**)element1) >
        (*(data**)element2)->get_rank(*(data**)element2);
}

void rank_sort(struct data* elements[], size_t size) {
    qsort(elements, size, 4, compare);
}

/*
int get_rank_func(const struct data* A) {
    return A->a;
}

int main() {
    int n = 5;
    struct data* elements[n];
    for (int i = 0; i != n; ++i) {
        elements[i] = malloc(sizeof(data));
        elements[i]->get_rank = get_rank_func;
        elements[i]->a = n - i;
    }
    rank_sort(elements, n);

    for (int i = 0; i != n; ++i) {
        printf("%d ", elements[i]->a);
        free(elements[i]);
    }
    printf("\n");
}*/