#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int mysys(const char* str) {
	int pid, status;
	if ((pid = fork()) == 0) {
		execl("/bin/sh", "/bin/sh", "-c", str, (char*)NULL);
		_exit(127);
	} else if (pid < 0) {
		return -1;
	} else {
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) {
			return 128 + WTERMSIG(status);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) <= 127) {
			return WEXITSTATUS(status);
		}
	}
	return 1;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "incorrect input\n");
        return 0;
    }

    int status1 = mysys(argv[1]), status2 = 0;
    if (status1) {
    	status2 = mysys(argv[2]);
    }
    if ((status1 == 0) || (status2 == 0)) {
    	return mysys(argv[3]) != 0;
    } else {
    	return 1;
    }
}