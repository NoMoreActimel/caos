#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int cnt = -1;
volatile char end_counting = 0;

void f(int n) {
    ++cnt;
    if (cnt == 4) {
        _exit(0);
    }
    printf("%d\n", cnt);
    fflush(stdout);
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = f;
    sigaction(SIGINT, &sa, NULL);

    int pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);

    while (1) {
        pause();
    }
    return 0;
}