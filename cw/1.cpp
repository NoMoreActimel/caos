#include <iostream>

struct S {
	int min;
	int max;
	int average;
};

struct Node {
	int value;
	Node* next;
};

extern "C" void aggregate(Node*, S*);

int main() {
	Node* p1 = new Node;
	p1->value = 1;
	Node* p2 = new Node;
	p2->value = 2;
	Node* p3 = new Node;
	p3->value = 3;

	p1->next = p2;
	p2->next = p3;

	S* stats = new S;
	aggregate(p1, stats);

	std::cout << stats->min << ' ' << stats->max << ' ' << stats->average << '\n';

	delete p1;
	delete p2;
	delete p3;
}