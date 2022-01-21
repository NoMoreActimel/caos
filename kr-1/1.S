	.global main
main:
	push %ebp
	mov %esp, %ebp

loop:
	movl head, %eax
	cmp $0, %eax
	jz exit




exit:
	movl %eax, head
	mov %ebp, %esp
	pop %ebp
	ret

	.data
cnt_elems:
	.int 0