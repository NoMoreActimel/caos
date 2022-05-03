#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match(const char *string, char *pattern) {
    int    status;
    regex_t    re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    char* regex = argv[1];
    char* name = argv[2];
    if (match(name, regex)) {
        printf("'%s' matches '%s'\n", name, regex);
    } else {
        printf("'%s' mismatches '%s'\n", name, regex);
    }
    return 0;
}