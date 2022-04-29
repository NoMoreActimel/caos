#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signalfd.h>

volatile int turn = 0; 
// first - 0, second - 1

void f(int n) {
    turn = 1 - turn;
}

void close_fd(int fd[2]) {
    close(fd[0]);
    close(fd[1]);
}

void throw_error(char* comment) {
    fprintf(stderr, "%s", comment);
    _exit(1);
}

void pingpong(int child_num, int fd[2], int other_pid, int n) {
    int cur;
    while (1) {
        if (turn == child_num) {
            if (read(fd[0], &cur, sizeof(cur)) == -1) {
                throw_error("read error\n");
            }

            printf("%d %d\n", child_num + 1, cur);
            fflush(stdout);
            ++cur;

            if (cur == n + 1) {
                kill(other_pid, SIGINT);
                _exit(0);
            }

            if (write(fd[1], &cur, sizeof(cur)) == -1) {
                throw_error("write_error\n");
            }

            kill(other_pid, SIGUSR1);
            turn = 1 - turn;
            pause();
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        throw_error("input error\n");
    }

    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = f;
    sigaction(SIGUSR1, &sa, NULL);

    int n = atoi(argv[1]);

    int fd[2];  
    if (pipe(fd) < 0) { 
        throw_error("pipe error\n");
    }

    int pid1, pid2;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    signalfd(fd[0], &mask, 0);

    if ((pid1 = fork()) == 0) {
        if (read(fd[0], &pid2, sizeof(pid2)) == -1) {
            close_fd(fd);
            throw_error("read error\n");
        }
        pingpong(0, fd, pid2, n);
    } else if (pid1 < 0) {
        close_fd(fd);
        throw_error("fork_error\n");
    }

    if ((pid2 = fork()) == 0) {
        pingpong(1, fd, pid1, n);
    } else if (pid1 < 0) {
        close_fd(fd);
        throw_error("fork_error\n");
    }

    if (write(fd[1], &pid2, sizeof(pid2)) == -1) {
        close_fd(fd);
        throw_error("write_error\n");
    }
    int start = 1;
    if (write(fd[1], &start, sizeof(start)) == -1) {
        close_fd(fd);
        throw_error("write_error\n");
    }

    wait(NULL);
    wait(NULL);
    close_fd(fd);
    return 0;
}