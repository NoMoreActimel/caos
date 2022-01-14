// #include <stdio.h>

// typedef int STYPE;
// typedef unsigned int UTYPE;

int bitcount(STYPE value) {
	UTYPE unsigned_value = (UTYPE)value;
	int bits_cnt = 0;

	while (unsigned_value) {
		if (unsigned_value != ((unsigned_value >> 1) << 1)) {
			++bits_cnt;
		}

		unsigned_value >>= 1;
	}

	return bits_cnt;
}

/*
int main() {
	STYPE value;

    FILE* input_file = fopen("input.txt", "r");
    fscanf(input_file, "%d", &value);
	printf("%d\n", bitcount(value));
}
*/