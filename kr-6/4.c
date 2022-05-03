#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "incorrect input\n");
        return 1;
    }

    int del = 1;
    while(argv[del][0] != ';') {
        ++del;
    }
    char* cmd1 = argv[1];
    char* args1[del];
    for (int i = 1; i < del; ++i) {
        args1[i - 1] = argv[i];
    }

    args1[del - 1] = (char*)(NULL);

    char* cmd2 = argv[del + 1];
    char* args2[argc - del];
    for (int i = del + 1; i < argc; ++i) {
        args2[i - del - 1] = argv[i];
    }
    args2[argc - del - 1] = (char*)(NULL);
    
    int pid1, pid2;

    if ((pid1 = fork()) == 0) {
        execvp(cmd1, args1);
        _exit(1);
    } else if (pid1 < 0) {
        fprintf(stderr, "fork error\n");
        _exit(1);
    }

    if ((pid2 = fork()) == 0) {
        execvp(cmd2, args2);
        _exit(1);
    } else if (pid1 < 0) {
        fprintf(stderr, "fork error\n");
        _exit(2);
    }

    wait(NULL);

    kill(pid1, SIGKILL);
    kill(pid2, SIGKILL);

    return 0;
}