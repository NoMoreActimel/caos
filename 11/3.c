#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pid, status;
	if ((pid = fork()) == 0) {
		// in child now
		if ((pid = fork()) == 0) {
			printf("3 ");
		} else {
			wait(&status);
			printf("2 ");
		}
	} else {
		wait(&status);
		printf("1\n");
	}
}