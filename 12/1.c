#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "incorrect input\n");
        return 0;
    }

    int pid, status;
    if ((pid = fork()) == 0) {
        int in_fd = open(argv[2], O_RDONLY);
        if (in_fd == -1) {
            fprintf(stderr, "error opening input file\n");
            return 2;
        }
        int out_fd = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, 0666);
        if (out_fd == -1) {
            fprintf(stderr, "error opening output file\n");
            return 2;
        }

        if (dup2(in_fd, STDIN_FILENO) == -1) {
            fprintf(stderr, "dup2 input error\n");
            return 3;
        }
        close(in_fd);

        if (dup2(out_fd, STDOUT_FILENO) == -1) {
            fprintf(stderr, "dup2 output error\n");
            return 3;
        }
        close(out_fd);
        
        execlp(argv[1], argv[1], (char*)NULL);
    } else if (pid < 0) {
        fprintf(stderr, "fork error\n");
        return 0;
    } else {
        wait(&status);
        if (WEXITSTATUS(status)) {
            fprintf(stderr, "execlp error\n");
            return 0;
        }
    }

    return 0;
}