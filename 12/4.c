#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "incorrect input\n");
        return 1;
    }
    char* xdg_runtime_dir = getenv("XDG_RUNTIME_DIR");
    char pathname[PATH_MAX];
    char filename[16];
    sprintf(filename, "%d", (int)getpid());
    strcat(filename, ".py");

    if (xdg_runtime_dir) {
        strcpy(pathname, xdg_runtime_dir);
        strcat(pathname, filename);
    } else {
        char* tmp_dir = getenv("TMP_DIR");

        if (tmp_dir) {
            strcpy(pathname, tmp_dir);
            strcat(pathname, filename);
        } else {
            strcpy(pathname, "/tmp/");
            strcat(pathname, filename);
        }
    }

    
    char* args[argc + 2];
    args[0] = pathname;
    for (int i = 0; i < argc; ++i) {
        args[i + 1] = argv[i];
    }
    args[argc + 1] = (char*)NULL;

    
    int fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0700);
    FILE* f = fdopen(fd, "w");
    assert(pathname[strlen(pathname)] == '\0');
    assert(f != NULL);  
    fprintf(f,
            "#!/usr/bin/python3\n"
            "import os, sys\n"
            "from functools import reduce\n"
            "A = sys.argv\n"
            "print(reduce((lambda x, y: int(x) * int(y)), A[2:]))\n"
            "os.remove('%s')\n",
            pathname);
    fclose(f);

    execv(pathname, args);
}