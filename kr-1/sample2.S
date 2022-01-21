	.global main, mul2, value

main:
	call readi32
	mov %eax, value
	call mul2
	mov value, %eax
	call writei32
	call finish

mul2:
	push %ebp
	mov %esp, %ebp

	mov value, %edx
	sal $1, %edx
	jo exit

	mov %edx, value
	
exit:
	mov %ebp, %esp
	pop %ebp
	ret

	.data
value:
	.int 0
