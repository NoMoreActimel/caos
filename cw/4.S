	.global main, process
main:
	sub $4, %esp
	push %ebp
	mov %esp, %ebp
	add $8, %esp
	call process
	call writei32
	call finish