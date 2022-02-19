#include <sys/syscall.h>
#include <stdint.h>
#include <stdio.h>

void print_parent_arg() {
    uint32_t u;
    asm volatile (
        "mov (%%ebp), %%ecx\n\t"
        "mov 8(%%ecx), %%eax\n\t"
        : "=a"(u)
        :
        : "ecx"); 
    printf("%x\n", u);
}
