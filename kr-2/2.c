#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

bool ith_bit(uint64_t a, int i) {
    return (a >> i) & 1;
}

void fprint7(FILE* f, int64_t number) {
    if (number == 0) {
        fprintf(f, "%d", 0);
        return;
    }

    bool sign = false;
    bool intmin = false;
    if (number == INT64_MIN) {
        number = INT64_MAX;
        sign = true;
        intmin = true;
    }

    if (number < 0) {
        number = -number;
        sign = true;
    }

    char* buf = malloc(sizeof(char) * 30);

    int r = 0;
    int64_t q = number;
    int i = 0;
    int64_t prev_q = number;

    while (q) {
        q = q / 7;
        r = prev_q - 7 * q;
        prev_q = q;

        buf[i++] = r + 48;
    }

    if (intmin) {
        buf[0]++;
    }

    int sz = i;

    char *number7 = malloc(sizeof(char) * (sz + 1 + (int)(sign)));

    if (sign) {
        number7[0] = '-';
        for (int j = 0; j != sz; ++j) {
            number7[j + 1] = buf[sz - j - 1];
        }
        number7[sz + 1] = '\0';
    } else {
        for (int j = 0; j != sz; ++j) {
            number7[j] = buf[sz - j - 1];
        }
        number7[sz] = '\0';
    }

    fprintf(f, "%s", number7);
    free(buf);
    free(number7);
}

/*
int main () {
    fprint7(stdout, INT64_MIN);
}*/