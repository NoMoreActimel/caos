#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr, "incorrect input\n");
		return 1;
	}

	char* filepath = argv[1];
	int rows = atoi(argv[2]);
	int cols = atoi(argv[3]);

	int fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (ftruncate(fd, rows * cols * sizeof(double))) {
		fprintf(stderr, "ftruncate failed\n");
		return 1;
	}

	double* A = mmap(NULL, rows * cols * sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (A == MAP_FAILED) {
		fprintf(stderr, "mmap failed\n");
		return 1;
	}

	for (int i = 0; i != rows; ++i) {
		for (int j = 0; j != cols; ++j) {
			A[i * cols + j] = 2 * sin((double)(i)) + 4 * cos((double)(j) / 2);
		}
	}

    close(fd);
}