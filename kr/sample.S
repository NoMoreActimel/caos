	.global list_reverse
list_reverse:
	push %ebp
	mov %esp, %ebp

	movl head, %eax
	cmp $0, %eax
	jz exit

	movl 8(%eax), %edx
	movl $0, 8(%eax)

loop:
	cmp $0, %edx
	jz exit

	movl 8(%edx), %ecx
	movl %eax, 8(%edx)

	movl %edx, %eax
	movl %ecx, %edx

	jmp loop

exit:
	movl %eax, head
	mov %ebp, %esp
	pop %ebp
	ret







.global process, A, B, R

process:
	push %ebp
	mov %esp, %ebp

	mov A, %eax
	mov B, %edx
loop:
	cmp $0, %eax
	jz exit

	mov $1, %ecx
	and %eax, %ecx

	cmp $0, %ecx
	jz shift_AB

	xor %ecx, %ecx
	mov R, %ecx
	add %edx, %ecx
	mov %ecx, R

shift_AB:
	shr $1, %eax
	shl $1, %edx
	jmp loop

exit:
	mov %eax, A
	mov %edx, B

	mov %ebp, %esp
	pop %ebp
	ret

	.data
A:
	.int 0
B:
	.int 0
R:
	.int 0