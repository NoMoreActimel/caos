#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

void update(const char *replacement, char *newtext, char* oldtext, int beg){
    strncat(newtext, oldtext, beg);
    strcat(newtext, replacement);
}

int main(int argc, char *argv[]) {
    char* pattern = argv[1];
    regex_t reg;
    int cflags = REG_EXTENDED;
    regmatch_t  pmatch[1];
    char* text = argv[2];
    int length1 = strlen(text);
    char* replacement = argv[3];
    int lenght2 = strlen(replacement);
    char *buffer = malloc(length1*lenght2*sizeof(char));
    regoff_t    beg;
    regcomp(&reg, pattern, cflags);

    for (int i = 0; ; i++){
        if (regexec(&reg, text, ARRAY_SIZE(pmatch), pmatch, 0))
            break;
        beg = pmatch[0].rm_so;
        update(replacement, buffer, text, (int) beg);
        text += pmatch[0].rm_eo;
    }

    free(buffer);
    regfree(&reg);
    exit(EXIT_SUCCESS);
    return 0;
}