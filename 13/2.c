#include <stdio.h>
#include <time.h>
#include <stdlib.h>

enum { MIN_SEC = 60,
	   HOUR_SEC = 3600,
	   DAY_SEC = 86400,
	   START_YEAR = 1900 };


// 0123456789
// 2022/10/10

// 0123456789
// hh:mm:ss

time_t parse_string(FILE* fptr) {
	char line[1001];
	if (fgets(line, 1000, fptr) == NULL) {
		return -1;
	}

	char year_str[5];
	char month_str[3];
	char day_str[3];
	char hour_str[3];
	char min_str[3];
	char sec_str[3];

	for (int i = 0; i != 4; ++i) {
		year_str[i] = line[i];
	}
	for (int i = 0; i != 2; ++i) {
		month_str[i] = line[5 + i];
		day_str[i] = line[8 + i];
	}

	int ind = 10;
	while (line[ind] == ' ') {
		++ind;
	}

	for (int i = 0; i != 2; ++i) {
		hour_str[i] = line[ind + i];
		min_str[i] = line[ind + 3 + i];
		sec_str[i] = line[ind + 6 + i];
	}

	struct tm date;
	date.tm_year = atoi(year_str) - START_YEAR;
	date.tm_mon = atoi(month_str) - 1;
	date.tm_mday = atoi(day_str);
	date.tm_hour = atoi(hour_str);
	date.tm_min = atoi(min_str);
	date.tm_sec = atoi(sec_str);
	date.tm_isdst = -1;

	return mktime(&date);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "incorrect input\n");
		return 1;
	}

	FILE* fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		fprintf(stderr, "error opening file\n");
		return 1;
	}

	time_t prev_time = parse_string(fptr);
	time_t time;
	while ((time = parse_string(fptr)) != -1) {
		printf("%ld\n", time - prev_time);
		prev_time = time;
	}

	fclose(fptr);
}