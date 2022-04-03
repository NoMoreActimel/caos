#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

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
	return 0;
}