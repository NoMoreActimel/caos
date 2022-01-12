#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum {
	BUF_SIZE = 4096,
};

ssize_t copy_file(int in_fd, int out_fd) {
	if (in_fd < 0 || out_fd < 0) {
		return -1;
	}

	char buf[BUF_SIZE];
	ssize_t sum_size = 0;
	ssize_t current_size, written_size;
	
	while ((current_size = read(in_fd, buf, BUF_SIZE)) > 0) {
		if (current_size < 0) {
			return -1;
		}
		sum_size += current_size;

		char* cur_buf_ptr = buf;
		while ((written_size = write(out_fd, cur_buf_ptr, current_size)) > 0) {
			if (written_size == current_size) {
				break;
			} else if (written_size < 0) {
				return -1;
			}

			cur_buf_ptr += written_size;
			current_size -= written_size;
		}

	}

	if (current_size < 0) {
		return -1;
	}

	return sum_size;
}


int main() {
	copy_file(STDIN_FILENO, STDOUT_FILENO);	
}
