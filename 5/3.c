// #include <stdio.h>
#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
	uint32_t s = v1 + v2;
	if (s < v1 || s < v2) {
		s = -1;
	}

	return s;
}

/*
int main() {
	uint32_t v1, v2;
	scanf("%u %u", &v1, &v2);
	printf("%u\n", satsum(v1, v2));
}
*/