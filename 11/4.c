#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int pid, status;
	int x;
	bool child_process = false;
 	 
	while (scanf("%d", &x) == 1) {
		if ((pid = fork()) == 0) {
			child_process = true;
		} else if (pid == -1) {
			return 1;
		} else {
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
				if (child_process) {
					return 1;
				} else {
					printf("-1\n");
					return 0;
				}
			}
			printf("%d\n", x);
			return 0;
		}
	}
}