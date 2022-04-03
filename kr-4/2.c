#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
	int n = atoi(argv[1]);
	int pid;
	int i = 0;
	int xyzzy = 0;
	int is_par = 1;

	i++;
	if ((pid = fork()) == 0) {
		return i;
	}

	while (i != 2 * n) {
		i++;
		if ((pid = fork()) == 0) {
			is_par = 0;
			if (i != 2 * n) {
				i++;
				if ((pid = fork()) == 0) {
					exit(i);
				}
			} else {
				return i;
			}
		} else {
			if (is_par) {
				break;
			} else {
				int a, b;
				wait(&a);
				wait(&b);
				xyzzy = frobnicate(WEXITSTATUS(a), WEXITSTATUS(b));
				exit(xyzzy);
			}
		}
	}


	int par_a, par_b;
	wait(&par_a);
	wait(&par_b);
	xyzzy = frobnicate(WEXITSTATUS(par_a), WEXITSTATUS(par_b));

	printf("%d\n", xyzzy);
	return 0;
}