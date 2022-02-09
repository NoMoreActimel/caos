#include <sys/syscall.h>


void _start() {
    char* str = "hello world\n";
    asm volatile (
        "mov $12, %%edx\n\t"
        "mov %0, %%ecx\n\t"
        "mov $1, %%ebx\n\t"
        "mov $4, %%eax\n\t"
        "int $0x80\n\t"
        "mov $0, %%ebx\n\t"
        "mov $1, %%eax\n\t"
        "int $0x80\n\t"
        :
        : "m"(str)
        : "eax", "ebx", "ecx", "edx" );
}
