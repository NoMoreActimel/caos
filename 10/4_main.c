#include <stdio.h>
#include "4.c"

void bitwise_print(int x) {
	for (int i = 11; i != -1; --i) {
		printf("%d", ith_bit(x, i));
		if (i % 3 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}


int main() {
	char buf[16];
	perms_to_str(buf, 16, 0650);
	bitwise_print(0650);
	printf("%s\n", buf);
}