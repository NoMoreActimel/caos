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

bool starts_with_prefix(char* name, char* prefix) {
    if (strlen(name) < strlen(prefix)) {
        return false;
    }

    for (int i = 0; i != strlen(prefix); ++i) {
        if (name[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}


int main(int argc, char** argv) {
    if (argc < 3) {
        throw_error();
    }

    DIR* dir = opendir(argv[1]);
    char* prefix = argv[2];
    if (!dir) {
        throw_error();
    }

    struct dirent* ent;

    while ((ent = readdir(dir))) {
        char* child_name = ent->d_name;
        char *child_path = malloc(strlen(argv[1]) + strlen(child_name) + 2);
        sprintf(child_path, "%s/%s", argv[1], child_name);

        struct stat s;
        stat(child_path, &s);
        if (S_ISREG(s.st_mode   ) && starts_with_prefix(child_name, prefix)) {
            for (int i = 0; i != strlen(child_name); ++i) {
                if (child_name[i] != '\0') {
                    printf("%c", child_name[i]);
                }
            }
            printf("\n");
        }

        free(child_path);
    }
    closedir(dir);
}