#include <inttypes.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int count1 = 0;
volatile int count2 = 0;
volatile char is_sig1 = 0;
volatile char end_flag = 0;

void f1(int n) {
    is_sig1 = 1;
}

void f2(int n) {
    is_sig1 = 0;
    ++count2;
}

void f3(int n) {
    end_flag = 1;
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;

    sa.sa_handler = f1;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_handler = f2;
    sigaction(SIGUSR2, &sa, NULL);

    sa.sa_handler = f3;
    sigaction(SIGTERM, &sa, NULL);

    sigset_t blocked_sig_mask;
    sigemptyset(&blocked_sig_mask);
    sigaddset(&blocked_sig_mask, SIGUSR1);
    sigaddset(&blocked_sig_mask, SIGUSR2);
    sigaddset(&blocked_sig_mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &blocked_sig_mask, NULL);

    sigset_t all_sig_mask;
    sigemptyset(&all_sig_mask);

    int pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);

    while(1) {
        sigsuspend(&all_sig_mask);
        if (end_flag) {
            break;
        } else if (is_sig1) {
            printf("%d %d\n", count1, count2);
            fflush(stdout);
            ++count1;
        }
    }

    return 0;
}