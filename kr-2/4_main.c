#include <stdio.h>
#include "4.c"

int main() {
	char* v1 = "pre-release";
	char* v2 = "AcmeOffice 10";

	printf("%d\n", vercmp(v1, v2));
	// free(v1);
	// free(v2);
}