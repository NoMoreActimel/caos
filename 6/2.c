#include <stdio.h>

typedef int STYPE;
typedef unsigned int UTYPE;

int bitcount(STYPE value) {
	int bits_cnt = 0;
	while (value) {
		value >> 1;
		++bits_cnt;
	}
	return bits_cnt;
}

int main() {

}