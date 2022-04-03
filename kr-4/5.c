#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>

int64_t generate_or_fail(size_t i); /* {
		return i;
}*/

int64_t* parallel_populate(size_t N) {
	int64_t* A = mmap(NULL, N * sizeof(int64_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (A == MAP_FAILED) {
		fprintf(stderr, "mmap failed\n");
		return NULL;
	}

	int* children_pids = malloc(N * sizeof(int));

	int pid;
	for (int i = 0; i != N; ++i) {
		if ((pid = fork()) == 0) {
			A[i] = -1;
			A[i] = generate_or_fail(i);
			exit(0);
		} else {
			children_pids[i] = pid;
		}
	}

	for (int i = 0; i != N; ++i) {
		int status;
		waitpid(children_pids[i], &status, 0);
		if (WEXITSTATUS(status)) {
			A[i] = -1;
		}
	}

	free(children_pids);
	return A;
}

/*
int main() {
	int n = 3;
	int64_t* A = parallel_populate(n);
	for (int i = 0; i != n; ++i) {
		printf("%lld ", A[i]);
	}
	printf("\n");
}*/