#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr, "incorrect input\n");
		return 1;
	}

	char* filename = argv[1];
	int rows = atoi(argv[2]);
	int cols = atoi(argv[3]);

	int fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (ftruncate(fd, rows * cols * sizeof(int))) {
		fprintf(stderr, "ftruncate failed\n");
		return 1;
	}

	int* A = mmap(NULL, rows * cols * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (A == MAP_FAILED) {
		fprintf(stderr, "mmap failed\n");
		return 1;
	}

    int di = 0, dj = 0;
    int rows_left = rows, cols_left = cols;
    int x = 1;

    while (rows_left > 0 && cols_left > 0) {
    	if (rows_left == 1) {
    		for (int j = dj; j < cols - dj; ++j) {
    			A[di * cols + j] = x++;
    		}
    	} else if (cols_left == 1) {
    		for (int i = di; i < rows - di; ++i) {
    			A[i * cols + dj] = x++;
    		}
	    } else {
	        for (int j = dj; j < cols - dj; ++j) {
	        	A[di * cols + j] = x++;
	        }
	        for (int i = di + 1; i < rows - di; ++i) {
	        	A[i * cols + cols - dj - 1] = x++;
	        }
	        for (int j = cols - dj - 2; j > dj; --j) {
	        	A[(rows - di - 1) * cols + j] = x++;
	        }
	        for (int i = rows - di - 1; i > di; --i) {
	        	A[i * cols + dj] = x++;
	        }
    	}

        di++;
        dj++;

        rows_left -= 2;
        cols_left -= 2;
    }

    close(fd);
}