#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>


void throw_error() {
	printf("incorrect input\n");
	exit(1);
}


int main(int argc, char** argv) {
	uint64_t sum_sz = 0;

	for (int i = 1; i != argc; ++i) {
		char* file_name = argv[i];
		struct stat s;

		if (lstat(file_name, &s) < 0) {
			// throw_error();
			continue;
		}

		// printf("%s\n", file_name);
		// printf("%" PRId64 "\n\n", s.st_size);

		if (s.st_nlink == 1 && S_ISREG(s.st_mode) && !S_ISLNK(s.st_mode)) {
			sum_sz += s.st_size;
		}
	}

	printf("%" PRIu64 "\n", sum_sz);
}