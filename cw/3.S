	.global mul2

mul2:
	push %ebp
	mov %esp, %ebp

	mov 8(%esp), %edx
	mov (%edx), %eax
	sal $1, %eax
	jo exit

	mov %eax, (%edx)
	
exit:
	mov %ebp, %esp
	pop %ebp
	ret