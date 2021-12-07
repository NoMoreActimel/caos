#include <iostream>

extern "C" void mul2(int* value);

int main() {
	int* value = new int;
	std::cin >> *value;
	mul2(value);
	std::cout << *value << '\n';
}