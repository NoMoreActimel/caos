#include <iostream>
#include <algorithm>
#include <cstdlib>

extern "C" void* sort_by_abs(int16_t*, int);

void first_test() {
	int16_t* a = new int16_t[10];	
	a[0] = 1;
	a[1] = -1;
	a[2] = 2;
	a[3] = -3;
	a[4] = 4;
	a[5] = -5;
	a[6] = 0;
	a[7] = 4;
	a[8] = 10;
	a[9] = -1;

	for (int i = 0; i != 10; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';

	sort_by_abs(a, 10);

	std::cout << "sorted: ";
	for (int i = 0; i != 10; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';

	delete [] a;
}

void second_test() {
	int16_t* a = new int16_t[5];
	a[0] = -4;
	a[1] = -2;
	a[2] = 0;
	a[3] = 1;
	a[4] = 3;

	for (int i = 0; i != 5; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';

	sort_by_abs(a, 5);

	std::cout << "sorted: ";
	for (int i = 0; i != 5; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';

	delete [] a;
}

int main() {
	first_test();
}