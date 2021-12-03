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

	.global main
main:
	// ebx - size of cur_string
	// edi - pointer to the first elem
	mov $0, %ebx
	mov $string, %edi

loop_read:
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

	cmp $10, %al
	jz nl_print_string

	cmp $10, %ebx
	jz print_string

loop_continue:
	movb %al, (%edi)
	add $1, %edi
	add $1, %ebx

	jmp loop_read

nl_print_string:
	push %eax
	movb $10, (%edi)
	add $1, %edi
	add $1, %ebx

	sub %ebx, %edi
	push %ebx
	push %edi
	call print_str
	add $8, %esp

	mov $0, %ebx
	pop %eax
	jmp loop_read

print_string:
	push %eax
	movb $10, (%edi)
	add $1, %edi
	add $1, %ebx

	sub %ebx, %edi
	push %ebx
	push %edi
	call print_str
	add $8, %esp

	mov $0, %ebx
	pop %eax
	jmp loop_continue


print_exit:
	movb $10, (%edi)
	add $1, %edi
	add $1, %ebx

	sub %ebx, %edi
	push %ebx
	push %edi
	call print_str
	add $8, %esp

	mov $0, %ebx
	jmp exit

exit:
	cmp $0, %ebx
	jnz print_exit

	mov $SYS_EXIT, %eax
	mov $0, %ebx
	int $0x80

fail:
	mov $SYS_EXIT, %eax
	mov $1, %ebx
	int $0x80

	.data
string:
	.skip 20