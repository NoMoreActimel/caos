#include <inttypes.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile char mode = 0;

void f1(int n) {
    mode = 0;
}

void f2(int n) {
    mode = 1;
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = f1;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = f2;
    sigaction(SIGUSR2, &sa, NULL);

    int pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);

    int32_t x;
    int64_t res;
    while(scanf("%d", &x) == 1) {
        if (mode == 0) {
            res = -(int64_t)(x);
        } else {
            res = (int64_t)(x) * (int64_t)(x);
        }
        printf("%" PRId64 "\n", res);
        fflush(stdout);
    }
}