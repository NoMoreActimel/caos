#include <stdio.h>

int mystrcmp(const char* str1, const char* str2) {
	unsigned char* p1 = (unsigned char*)str1;
	unsigned char* p2 = (unsigned char*)str2;

	while (*p1 != '\0' || *p2 != '\0') {
		if (*p1 == '\0') {
			return -1;
		} else if (*p2 == '\0') {
			return 1;
		}

		if (*p1 < *p2) {
			return -1;
		} else if (*p2 < *p1) {
			return 1;
		}

		++p1;
		++p2;
	}
	return 0;
}


int main() {
	char str1[] = "am i";
	char str2[] = "am i shure i am?";

	printf("%d\n", mystrcmp(str1, str2));
}
