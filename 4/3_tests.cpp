#include <iostream>
#include <stdio.h>

extern "C" void* obrabotka_call();

struct S {
	S* next;
	int m1[12];
	int m2[12];
};

S* p = nullptr;

int main() {
	register void* ebx asm("ebx");
	register int esi asm("esi");
	register int edi asm("edi");

	p = new S();
	for (int i = 0; i != 12; ++i) {
		p->m1[i] = -i - 1;
		p->m2[i] = -12 + i;
	}
	/*
	S* p2 = new S();
	p->next = p2;

	for (int i = 0; i != 12; ++i) {
		p2->m1[i] = -i - 1;
		p2->m2[i] = -12 + i;
	}*/

	obrabotka_call();
}