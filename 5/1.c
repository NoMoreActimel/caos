#include <stdio.h>

void normalize_path(char* buf) {
	char* nbuf;
	for (nbuf = buf; *buf != '\0'; ++nbuf, ++buf) {
		if (nbuf != buf) {
			*nbuf = *buf;
		}
		if (*buf == '/' && *(buf + 1) == '/') {
			while (*(buf + 1) == '/') {
				++buf;
			}
		}
	}
	*nbuf = '\0';
}

int main() {
	char buf[] = "////asdad///adads ad////";
	//scanf("%s", buf);
	normalize_path(buf);
	printf("%s\n", buf);
	return 0;
}