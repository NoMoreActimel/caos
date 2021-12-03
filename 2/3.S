	.global process

process:
	push %ebp
	mov %esp, %ebp

input_loop:
	call readi32
	jc output_loop

	push %eax
	jmp input_loop

output_loop:
	cmp %esp, %ebp
	jz exit

	pop %eax
	call writei32

	jmp output_loop

exit:
	mov %ebp, %esp
	pop %ebp
	ret