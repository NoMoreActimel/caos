#include <stdlib.h>
#include <stdbool.h>

// 876 543 210
// rwx rwx rwx
// 110 110 100 

bool ith_bit(int x, int i) {
	return (x >> i) & 1;
}

const char *perms_to_str(char *buf, size_t size, int perms) {
	if (!size) {
		return buf;
	}
	if (size == 1) {
		buf[0] = '\0';
		return buf;
	}

	int sz = size - 1;
	if (sz > 9) {
		sz = 9;
	}

	for (int i = 0; i != sz; ++i) {
		bool perm_bit = ith_bit(perms, 8 - i);
		if (perm_bit) {
			if ((i % 3) == 0) {
				buf[i] = 'r';
			} else if ((i % 3) == 1) {
				buf[i] = 'w';
			} else {
				buf[i] = 'x';
			}
		} else {
			buf[i] = '-';
		}
	}

	if (sz >= 3) {
		bool suid_bit = ith_bit(perms, 11);
		if (suid_bit && (ith_bit(perms, 3) || ith_bit(perms, 0))) {
			buf[2] = 's';
		}

		if (sz >= 6) {
			bool sgid_bit = ith_bit(perms, 10);
			if (sgid_bit && ith_bit(perms, 0)) {
				buf[5] = 's';
			}

			if (sz == 9) {
				bool sticky_bit = ith_bit(perms, 9);
				if (sticky_bit && ith_bit(perms, 1) && ith_bit(perms, 0)) {
					buf[8] = 't';
				}
			}
		}
	}

	buf[sz] = '\0';
	return buf;
}