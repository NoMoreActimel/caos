#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// #include "1.S"

extern int run_on_stack(void* func, void* arg, void* stack_bottom);

int i_love_large_stacks(void* arg) {
    int local_array[4 << 20]; // 16-megabyte array
    local_array[0] = 42;
    local_array[1] = 0;
    return 3 - local_array[1];
}


int main() {
    const size_t stacksize = 50 << 20; // 50 MB
    char* stack = (char*)malloc(stacksize);
    int result = run_on_stack(i_love_large_stacks, NULL, stack + stacksize);
    assert(result == 3);
    return 0;
}