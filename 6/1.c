#include <stdio.h>

int main() {
	unsigned a, b, d, m;

	if (scanf("%u%u", &a, &b) != 2) {
		printf("incorrect numbers\n");
	} else {
		if (b > a) {
			d = b - a;
			m = a + d / 2;
		} else {
			d = a - b;
			m = b + d / 2;
		}

		printf("%u\n", m);
	}

	return 0;
}