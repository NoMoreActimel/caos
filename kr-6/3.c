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

void throw_error(char* str) {
    printf("%s\n", str);
    exit(1);
}

bool starts_with_prefix(char* path, char* prefix) {
    // printf("%s\n%s\n", path, prefix);
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL) {
        throw_error("can't open file");
    }

    int i = 0;
    int n = strlen(prefix);
    char c;
    while (((c = fgetc(fptr)) != EOF) && (i != n)) {
        if (c != prefix[i]) {
            return false;
        }
        ++i;
    }

    if (i != n) {
        return false;
    }

    return true;
}


int main(int argc, char** argv) {
    if (argc != 3) {
        throw_error("incorrect input");
    }

    DIR* dir = opendir(argv[1]);
    char* prefix = argv[2];
    if (!dir) {
        throw_error("can't open directory");
    }

    struct dirent* ent;

    while ((ent = readdir(dir))) {
        char* child_name = ent->d_name;
        char *child_path = malloc(strlen(argv[1]) + strlen(child_name) + 2);
        sprintf(child_path, "%s/%s", argv[1], child_name);

        struct stat s;
        stat(child_path, &s);
        if (S_ISREG(s.st_mode) && starts_with_prefix(child_path, prefix)) {
            bool is_empty = true;
            for (int i = 0; i != strlen(child_name); ++i) {
                if (child_name[i] != '\0') {
                    printf("%c", child_name[i]);
                    is_empty = false;
                }
            }

            if (!is_empty) {
                printf("\n");
            }
        }

        free(child_path);
    }
    closedir(dir);
}