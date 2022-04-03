#include "2.c"
#include <stdio.h>

int main() {
	int ret = mysys("echo \"no way\"");
	printf("%d\n", ret);
	return 0;
}