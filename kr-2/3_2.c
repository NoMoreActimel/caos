#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int (*get_rank)(const struct data*);
    int a;
    char secret[];
} data;

int get_rank(const struct data* A) {
    return A->a;
}

void rank_sort(struct data* elements[], size_t size) {
	for (int i = 0; i != size - 1; ++i) {
		for (int j = i; j != size - 1; ++j) {
			if (((void(*))elements[j]->get_rank)(elements[j]) < ((void(*))elements[j + 1]->get_rank)(elements[j])) {
				data* tmp = elements[j];
				elements[j] = elements[j + 1];
				elements[j + 1] = tmp;
			}
		}
	}
}

int main() {
    int n = 5;
    struct data* elements[n];
    for (int i = 0; i != n; ++i) {
        elements[i] = malloc(sizeof(data));
        elements[i]->a = i;
    }
    rank_sort(elements, n);
}
