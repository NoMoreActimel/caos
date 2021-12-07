	.equ SYS_EXIT, 1
	.equ SYS_READ, 3
	.equ SYS_WRITE, 4
	.equ STDIN_FILENO, 0
	.equ STDOUT_FILENO, 1
	.equ BUF_SIZE, 1

read_str:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov $SYS_READ, %eax
	mov $STDIN_FILENO, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	int $0x80

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret

print_str:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov $SYS_WRITE, %eax
	mov $STDOUT_FILENO, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	int $0x80

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret

	.global main, cnt_lines, cnt_words, cnt_chars
main:
	// ebx - bool(is a word-char)
	mov $0, %ebx

loop:
	sub $BUF_SIZE, %esp	
	mov %esp, %esi
	push $BUF_SIZE
	push %esi
	call read_str
	add $8, %esp

	test %eax, %eax
	jz exit

	xor %eax, %eax
	movb (%esi), %al

	add $1, cnt_chars

	cmp $10, %al
	jz new_line

	cmp $32, %al
	jz space

	mov $1, %ebx
	jmp loop


new_line:
	add $1, cnt_lines

	cmp $0, %ebx
	jz loop

	add $1, cnt_words
	mov $0, %ebx
	jmp loop

space:
	cmp $0, %ebx
	jz loop

	add $1, cnt_words
	mov $0, %ebx
	jmp loop

exit:
	mov cnt_lines, %eax
	call writei32
	mov cnt_words, %eax
	call writei32
	mov cnt_chars, %eax
	call writei32

	mov $SYS_EXIT, %eax
	mov $0, %ebx
	int $0x80

fail:
	mov $SYS_EXIT, %eax
	mov $1, %ebx
	int $0x80

	.data
cnt_lines:
	.int 0
cnt_words:
	.int 0
cnt_chars:
	.int 0