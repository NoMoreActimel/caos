#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <inttypes.h>

int main() {
	int fds[2];
	if (pipe(fds) < 0) {
		close(fds[0]);
		close(fds[1]);
		return 0;
	}

	int pid1, status1;
	if ((pid1 = fork()) == 0) {
		close(fds[1]);
		int pid2, status2;
		if  ((pid2 = fork()) == 0) {
			int64_t s = 0;
			int32_t x = 0;

			while (read(fds[0], &x, sizeof(x)) > 0) {
				s += x;
			}

			close(fds[0]);
			printf("%" PRId64 "\n", s);
			fflush(stdout);
			_exit(0);
		} else if (pid2 < 0) {
			close(fds[0]);
			_exit(0);
		}

		waitpid(pid2, &status2, 0);
		_exit(0);
	} else if (pid1 < 0) {
		close(fds[0]);
		close(fds[1]);
		_exit(0);
	}

	int32_t x;
	while (scanf("%d", &x) == 1) {
		if (write(fds[1], &x, sizeof(x)) == -1) {
			break;
		}
	}

	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, &status1, 0);
	return 0;
}