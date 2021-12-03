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