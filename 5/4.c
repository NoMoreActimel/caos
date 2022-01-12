#include <unistd.h>
// #include <stdio.h>

enum {
	BUF_SIZE = 4096,
};

struct FileWriteState {
	int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int current_bufsize; // текущий размер буфера
};

static unsigned char buffer[BUF_SIZE];
struct FileWriteState out_ = {STDOUT_FILENO, buffer, BUF_SIZE, 0};
struct FileWriteState *stout = &out_;

void flush(struct FileWriteState *out) {
	write(out->fd, out->buf, out->current_bufsize);
	out->current_bufsize = 0;
}

void writechar(int c, struct FileWriteState* out) {
	*(out->buf + out->current_bufsize) = c;
	++out->current_bufsize;

	if (out->current_bufsize == BUF_SIZE) {
		flush(stout);
	}
}

/*
int main() {
	unsigned char str[] = "an example one";
	for (int i = 0; i != 10; ++i) {
		writechar(str[i], stout);
	}
	flush(stout);
	printf("\n");

	for (int i = 10; i != 14; ++i) {
		writechar(str[i], stout);
	}
	flush(stout);
}
*/