#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void close_fds(int fds1[2], int fds2[2]) {
	close(fds1[0]);
	close(fds1[1]);
	close(fds2[0]);
	close(fds2[1]);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "incorrect input\n");
		return 1;
	}

	int end = atoi(argv[1]);

	int pid1, status1;
	int pid2, status2;

	int c1c2[2];
	int c2c1[2];

	if (pipe(c1c2) < 0 || pipe(c2c1) < 0) {
		fprintf(stderr, "pipe error\n");
		return 1;
	}

	if ((pid1 = fork()) == 0) {
		int32_t x;
		close(c1c2[0]);
		close(c2c1[1]);

		while (1) {
			if (read(c2c1[0], &x, sizeof(x)) > 0) {
				if (x == end) {
					break;
				}

				printf("1 %d\n", x);
				fflush(stdout);
				++x;
				if (write(c1c2[1], &x, sizeof(x)) == -1) {
					break;
				}
			} else {
				break;
			}
		}

		close(c1c2[1]);
		close(c2c1[0]);
		_exit(0);
	} else if (pid1 < 0) {
		fprintf(stderr, "fork error\n");
		return 1;
	}

	if ((pid2 = fork()) == 0) {
		close(c1c2[1]);
		close(c2c1[0]);

		int32_t x = 1;
		if (write(c2c1[1], &x, sizeof(x)) == -1) {
			fprintf(stderr, "write error\n");
			close_fds(c1c2, c2c1);
			return 1;
		}

		while (1) {
			if (read(c1c2[0], &x, sizeof(x)) > 0) {
				if (x == end) {
					break;
				}

				printf("2 %d\n", x);
				fflush(stdout);
				++x;
				if (write(c2c1[1], &x, sizeof(x)) == -1) {
					break;
				}
			} else {
				break;
			}
		}

		close(c1c2[0]);
		close(c2c1[1]);
		_exit(0);
	} else if (pid2 < 0) {
		fprintf(stderr, "fork error\n");
		return 1;
	}

	close_fds(c1c2, c2c1);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	printf("Done\n");
	return 0;
}

