#include <dirent.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void throw_error() {
	printf("incorrect input\n");
	exit(1);
}

bool is_uppercase(char c) {
	return (65 <= c) && (c <= 90);
}

void add_if_relevant(char* name, char* path, uint64_t* sum_sz) {
	struct stat s;
	if (stat(path, &s) < 0) {
		return;
	}

	if (S_ISREG(s.st_mode) && s.st_uid == getuid() && is_uppercase(name[0])) {
		*sum_sz += s.st_size;
	}
}


int main(int argc, char** argv) {
	if (argc < 2) {
		throw_error();
	}

	DIR* dir = opendir(argv[1]);
	if (!dir) {
		throw_error();
	}

	struct dirent* ent;
	uint64_t sum_sz = 0;

	while ((ent = readdir(dir))) {
		char* child_name = ent->d_name;
      	char *child_path = malloc(strlen(argv[1]) + strlen(child_name) + 2);
      	sprintf(child_path, "%s/%s", argv[1], child_name);

		add_if_relevant(child_name, child_path, &sum_sz);
		free(child_path);
	}

	printf("%" PRIu64 "\n", sum_sz);
	closedir(dir);
}