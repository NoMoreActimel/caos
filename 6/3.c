#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* data;
    size_t size;
    size_t used_size;
} DynamicString;

void initDynamicString(DynamicString* str, size_t size) {
    str->data = malloc(size * sizeof(char));
    str->size = size;
    str->used_size = 0;
}

void freeDynamicString(DynamicString* str) {
    free(str->data);
    str->data = NULL;
    str->size = 0;
    str->used_size = 0;
}

void addCharDynamicString(DynamicString* str, char c) {
    if (str->used_size == str->size) {
        str->size *= 2;
        char* new_data = realloc(str->data, str->size * sizeof(char));

        if (new_data != NULL) {
            str->data = new_data;
        } else {
            freeDynamicString(str);
        }
    }

    str->data[str->used_size] = c;
    ++str->used_size;
}

char* getline2(FILE* f) {
    DynamicString str;
    int cur = 1;

    if ((cur = getc(f)) == EOF) {
        return NULL;
    } else {
        initDynamicString(&str, 1);
        addCharDynamicString(&str, cur);
        if (str.data == NULL) {
            return NULL;
        }

        if (cur == '\n') {
            addCharDynamicString(&str, '\0');
            return str.data;
        }
    }

    while ((cur = getc(f)) != EOF) {
        addCharDynamicString(&str, cur);
        if (str.data == NULL) {
            return NULL;
        }

        if (cur == '\n') {
            addCharDynamicString(&str, '\0');
            return str.data;
        }
    }

    addCharDynamicString(&str, '\0');
    return str.data;
}

/*
int main() {
    FILE* input_file = fopen("input.txt", "r");
    char* str = getline2(input_file);
    if (str == NULL) {
        printf("NULL returned\n");
    } else {
        printf("%s\n", str);
        free(str);
    }

    return 0;
}*/