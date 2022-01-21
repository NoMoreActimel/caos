#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t a, int32_t b) {
	int32_t c;

	if (a > 0 && b > 0) {
		if (__builtin_add_overflow(a, b, &c)) {
			return INT32_MAX;
		}
		return c;
	} 
	if (a < 0 && b < 0) {
		if (__builtin_add_overflow(a, b, &c)) {
			return INT32_MIN;
		}
		return c;
	}
	return a + b;
}

/*
int main() {
    int32_t a, b;
    scanf("%d%d", &a, &b);
    satsum(a, b);
    printf("%d\n", satsum(a, b));
}*/