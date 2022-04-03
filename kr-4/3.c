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

int main(int argc, char** argv) {
    for (int i = 1; i != argc; ++i) {
        char* path = argv[i];

        struct stat ls;
        if (lstat(path, &ls) < 0) {
            printf("%s (missing)\n", path);
        } else if (S_ISLNK(ls.st_mode)) {
            struct stat s;
            if (stat(path, &s) < 0) {
                printf("%s (broken symlink)\n", path);
            } else {
                printf("%s\n", path);
            }
        } else {
            printf("%s\n", path);
        }
    }
}