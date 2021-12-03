	.global process, A, B, R

process:
	push %ebp
	mov %esp, %ebp

	mov A, %eax
	mov B, %edx
loop:
	cmp $0, %eax
	jz exit

	mov $1, %ecx
	and %eax, %ecx

	cmp $0, %ecx
	jz shift_AB

	xor %ecx, %ecx
	mov R, %ecx
	add %edx, %ecx
	mov %ecx, R

shift_AB:
	shr $1, %eax
	shl $1, %edx
	jmp loop

exit:
	mov %eax, A
	mov %edx, B

	mov %ebp, %esp
	pop %ebp
	ret

	.data
A:
	.int 0
B:
	.int 0
R:
	.int 0