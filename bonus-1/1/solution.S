	.global rop
rop:
	push %ebp
	mov %esp, %ebp
	push %ebx

	push string
	call printf
	add $4, %esp

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret

	.global string
string:
	.asciz "Hello there"