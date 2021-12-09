	.global main, process

main:
	mov $main, %eax
	add $20, %eax
	push %eax
	mov %esp, %ebp
	call process
	call writei32
	call finish

process:
	mov $4, %eax
	call writei32
	mov %ebp, %esp
	pop %ebp
	ret

