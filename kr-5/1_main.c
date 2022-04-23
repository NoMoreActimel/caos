#include "1.c"
#include <stdio.h>

int main() {
	char outbuf[100];
	int x = interact("tac", "abc\ndef\n", outbuf);
	printf("%d\n", x);
	printf("%s\n", outbuf);
}