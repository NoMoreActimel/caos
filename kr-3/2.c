#include <stdint.h>
#include <inttypes.h>

void rdtsc_call(uint64_t* res) {
    uint32_t a, d;
    asm (
        "rdtsc\n\t"
        : "=a"(a), "=d"(d));
    *res = ((uint64_t)(d) << 32) + a;
}

void work_until_deadline(const uint64_t* deadline, void (*do_work)()) {
    uint64_t cur_time;
    rdtsc_call(&cur_time);
    while (cur_time < *deadline) {
        do_work();
        rdtsc_call(&cur_time);
    }
}