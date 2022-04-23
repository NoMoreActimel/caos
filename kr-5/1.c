#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

void close_fds(int fds1[2], int fds2[2]) {
	close(fds1[0]);
	close(fds1[1]);
	close(fds2[0]);
	close(fds2[1]);
}


int interact(const char* cmd, const char* input, char* outbuf) {
	int p2c[2];
	int c2p[2];
	if (pipe(p2c) < 0) {
		close(p2c[0]);
		close(p2c[1]);
		return 127;
	}
	if (pipe(c2p) < 0) {
		close(c2p[0]);
		close(c2p[1]);
		return 127;
	}

	int pid, status;
	if ((pid = fork()) == 0) {
		dup2(c2p[1], STDOUT_FILENO);
		dup2(p2c[0], STDIN_FILENO);
		close_fds(c2p, p2c);
		execlp(cmd, cmd, NULL);
		_exit(1);
	} else if (pid < 0) {
		close_fds(c2p, p2c);
		return 127;
	}

	if (write(p2c[1], input, strlen(input)) == -1) {
		return 127;
	}

	close(p2c[0]);
	close(p2c[1]);
	close(c2p[1]);
	waitpid(pid, &status, 0);

	int count_char = 0;
	if ((count_char = read(c2p[0], outbuf, SSIZE_MAX)) == -1) {
		return 127;
	}

	outbuf[count_char - 1] = '\0';

	close(c2p[0]);

	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	} else {
		return 127;
	}
}
