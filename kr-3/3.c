#include <sys/syscall.h>
#include <stdint.h>
#include <stdio.h>

void print_parent_arg() {
    uint32_t u;
    asm volatile (
        "mov 20(%%esp), %%ecx\n\t"
        "mov %%ecx, %0\n\t"
        : "=m"(u)
        :
        : "ecx"); 
    printf("%x\n", u);
}

void calling_fun(int x) {
    print_parent_arg();
}


int main() {
    calling_fun(2);
}