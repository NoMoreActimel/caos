#include <stdio.h>
#include <stdlib.h>

typedef struct RandomGenerator RandomGenerator;
void RandomGeneratorDestroy(RandomGenerator* rg);
int RandomGeneratorNext(RandomGenerator* rg);

typedef void (*destroy_t)(RandomGenerator*);
typedef int (*next_t)(RandomGenerator*);

typedef struct RandomOperations {
    destroy_t destroy;
    next_t next;
} RandomOperations;

typedef struct RandomGenerator {
    RandomOperations* ops;
    unsigned long long value;
} RandomGenerator;

static RandomOperations operations;

void initRandomOperations() {
    operations.destroy = RandomGeneratorDestroy;
    operations.next = RandomGeneratorNext;
}

RandomGenerator* random_create(int seed) {
    RandomGenerator* rg = malloc(sizeof(RandomGenerator));
    initRandomOperations();
    rg->ops = &operations;
    rg->value = seed;
    return rg;
}

void RandomGeneratorDestroy(RandomGenerator* rg) {
    free(rg);
}

int RandomGeneratorNext(RandomGenerator* rg) {
    rg->value = (rg->value * 1103515245 + 12345) % (1ull << 31);
    return (int)rg->value;
}

/*
int main() {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
}
*/