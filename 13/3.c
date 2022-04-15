#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	int fds[2];
	if (pipe(fds) < 0) {
		close(fds[0]);
		close(fds[1]);
		return 0;
	}

	int pid1, status1;
	if ((pid1 = fork()) == 0) {
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execlp(argv[1], argv[1], NULL);
		_exit(1);
	} else if (pid1 < 0) {
		close(fds[0]);
		close(fds[1]);
		return 0;
	}

	close(fds[1]);

	int pid2, status2;
	if ((pid2 = fork()) == 0) {
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		execlp(argv[2], argv[2], NULL);
		_exit(1);
	} else if (pid2 < 0) {
		close(fds[0]);
		return 0;
	}

	close(fds[0]);

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return 0;
}