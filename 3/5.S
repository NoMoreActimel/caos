	.equ SYS_EXIT, 1
	.equ SYS_READ, 3
	.equ SYS_WRITE, 4
	.equ STDIN_FILENO, 0
	.equ STDOUT_FILENO, 1
	.equ BUF_SIZE, 100000

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

	.global main
main:
	mov $0, %ebx

loop_read:
	sub $BUF_SIZE, %esp	
	mov %esp, %esi
	push $BUF_SIZE
	push %esi
	call read_str
	add $8, %esp

loop:

	xor %eax, %eax
	movb (%esi), %al

	test %eax, %eax
	jz exit

	cmp $0b11110000, %al
	jae utf8_4
	cmp $0b11100000, %al
	jae utf8_3
	cmp $0b11000000, %al
	jae utf8_2

utf8_1:
	add $1, %esi
	inc %ebx
	jmp loop

utf8_2:
	add $2, %esi
	inc %ebx
	jmp loop

utf8_3:
	add $3, %esi
	inc %ebx
	jmp loop

utf8_4:
	add $4, %esi
	inc %ebx
	jmp loop

exit:
	mov %ebx, %eax
	call writei32

	mov $SYS_EXIT, %eax
	mov $0, %ebx
	int $0x80

fail:
	mov $SYS_EXIT, %eax
	mov $1, %ebx
	int $0x80