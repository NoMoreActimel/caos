#include <dlfcn.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("incorrect input\n");
		return 1;
	}

	void* handle = dlopen("libm.so.6", RTLD_LAZY);
	if (!handle) {
		printf("incorrect handle\n");
		return 1;
	}

	double (*func)(double) = dlsym(handle, argv[1]);

	double x = 0.0;

	while (scanf("%lf", &x) != EOF) {
		printf("%.10g\n", func(x));
	}
}