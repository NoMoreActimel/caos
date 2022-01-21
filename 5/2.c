int mystrcmp(const char* str1, const char* str2) {
	unsigned char* p1 = (unsigned char*)str1;
	unsigned char* p2 = (unsigned char*)str2;

	while (*p1 != '\0' || *p2 != '\0') {
		if (*p1 != *p2) {
			return *p1 - *p2;
		}

		++p1;
		++p2;
	}
	return 0;
}