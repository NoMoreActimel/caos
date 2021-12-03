	.global main, list_reverse
main:
	call list_reverse
	call finish


list_reverse:
	push %ebp
	mov %esp, %ebp

	mov head, %eax
	cmp $0, %eax
	jz exit

	mov 8(%eax), %edx
	movl $0, 8(%eax)

loop:
	cmp $0, %edx
	jz exit

	mov 8(%edx), %ecx
	mov %eax, 8(%edx)

	mov %edx, %eax
	mov %ecx, %edx

	jmp loop

exit:
	mov %eax, head
	mov %ebp, %esp
	pop %ebp
	ret

	.data
head:
	.skip 12, 0
