#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "incorrect input\n");
        return 0;
    }

    int fdout = open(argv[3], O_APPEND | O_WRONLY, 0);

    int pid, status;
    if ((pid = fork()) == 0) {
    	dup2(fdout, 1);
    	close(fdout);
    	execlp(argv[1], argv[1], NULL);
    } else if (pid < 0) {
    	return 1;
    }

    wait(&status);
    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status))) {
    	if ((pid = fork()) == 0) {
    		dup2(fdout, 1);
    		close(fdout);
    		execlp(argv[2], argv[2], NULL);
    	} else if (pid < 0) {
    		return 1;
    	}

    	wait(&status);
    }

    close(fdout);
    return 0;
}