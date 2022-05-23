#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void f(int n) {
    char message[28] = "We communicate on my terms.\n";
    if (write(STDOUT_FILENO, &message, 28 * sizeof(char)) == -1) {
        fprintf(stderr, "write error\n");
        _exit(1);
    }
    fflush(stdout);
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = f;
    sigaction(SIGTERM, &sa, NULL);

    char c;
    while(read(STDIN_FILENO, &c, sizeof(c)) > 0) {
        if (write(STDOUT_FILENO, &c, sizeof(c)) == -1) {
            fprintf(stderr, "write error\n");
            _exit(1);
        }
        fflush(stdout);
    }
}