	.global main
main:
	xor %ebx, %ebx  // sum stored in %ebx
	xor %eax, %eax

loop:
	xor %ecx, %ecx

	mov %eax, %edx
	mov %ebx, %eax

	add %edx, %eax
	mov %eax, %ebx

	seto %cl
	jo overflow

	call readi32
	jnc loop


overflow:
	// make _111..1 if overflow
	mov $0x7FFFFFFF, %eax
	imull %ecx
	or %eax, %ebx

	// inverse 1st bit if overflow
	mov $0x80000000, %eax
	imull %ecx
	xor %eax, %ebx

	// if 1st bit == 1: 111..1 -> 100..0 - xor 011..1
	// if 1st bit == 0: 011..1 -> 011..1 - xor 000..0

	mov $0x7FFFFFFF, %eax
	imul %ecx

	mov %ebx, %edx
	shr $31, %edx  // 1st bit in %edx	
	imul %edx

	xor %eax, %ebx

exit:
	mov %ebx, %eax
	call writei32
	call finish
