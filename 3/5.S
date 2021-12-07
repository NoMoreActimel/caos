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

next_byte:
	push %ebp
	mov %esp, %ebp

	push $1
	push %esi
	call read_str
	add $8, %esp

	mov %ebp, %esp
	pop %ebp
	ret


	.global main
main:
	mov $0, %edi
	sub $1, %esp	
	mov %esp, %esi

next_char:
	call next_byte
	test %eax, %eax
	jz exit

	xor %ebx, %ebx
	movb (%esi), %bl

	inc %edi
	shl $1, %bl
	jc loop_cur_char
	jmp next_char
	
loop_cur_char:
	shl $1, %bl
	jnc next_char
	call next_byte
	jmp loop_cur_char


exit:
	mov %edi, %eax
	call writei32

	mov $SYS_EXIT, %eax
	mov $0, %ebx
	int $0x80

fail:
	mov $SYS_EXIT, %eax
	mov $1, %ebx
	int $0x80