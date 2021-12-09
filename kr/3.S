	.global mul2, value

mul2:
	push %ebp
	mov %esp, %ebp

	movl value, %edx
	mov (%edx), %eax
	sal $1, %eax
	jo exit

	mov %eax, (%edx)
	
exit:
	mov %ebp, %esp
	pop %ebp
	ret

	.data
value:
	.int 0
