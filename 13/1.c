#include <stdio.h>
#include <stdint.h>
#include <time.h>

enum { HOUR_SEC = 3600, DAY_SEC = 86400, START_YEAR = 1900 };

int main() {
	int x;
	time_t raw_date;
	struct tm* date;

	while (scanf("%d", &x) == 1) {
		time(&raw_date);

		int added_seconds;
		if (__builtin_mul_overflow(x, DAY_SEC, &added_seconds) ||
			__builtin_add_overflow(raw_date, added_seconds, &raw_date)) {
			printf("OVERFLOW\n");
			continue;
		}

		date = localtime(&raw_date);
		printf("%d-%02d-%02d\n", START_YEAR + date->tm_year, 1 + date->tm_mon, date->tm_mday);
	}
}