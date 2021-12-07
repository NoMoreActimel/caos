#include <iostream>

extern "C" void delegate(uint32_t, void(int, int, int*), int, int, int*);

void function(int a, int b, int* c) {
	*c = a + b;
}

int main() {
	int* c = new int(0);
	uint32_t n = 3;
	int a, b;
	std::cin >> a >> b;

	delegate(n, &function, a, b, c);
	std::cout << '\n';
	std::cout << *c << '\n';
	delete c;
}