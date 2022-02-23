#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void reallocate_array(char** array, int size) {
	char** new_array = malloc(size * 2 * sizeof(char*));
	if (!new_array) {
		return;
	}

	
}


void print_dir_subtree(DIR* dir) {
	struct dirent* ent;
	while ((ent = opendir(dir))) {
		if (ent->d_type == DT_DIR) {

		}
	}
}


void list_directories(char* current) {
	DIR* dir = opendir(current);
	if (!dir) {
		return;
	}

	struct dirent* ent;
	char** child_list = malloc(8 * sizeof(char*)); // dynamicly allocated
	int sz = 0;
	int reserved_sz = 8;

	while ((ent = readdir(dir))) {
		if (ent->d_type == DT_DIR) {
			child_list[sz] = ent->d_name;
			++sz;


		}
	}


}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "directory required\n");
		exit(1);
	}

	char* file_name = argv[1];

	
	DIR* dir = opendir(argv[1]);
	if (!dir) {
		exit(1);
	}

	struct dirent* ent;
	while ((ent = readdir(dir))) {
		printf("%s\n", ent->d_name);
	}

	closedir(dir);
}