	.global main
main:
	mov $0, %esi	// even
	mov $0, %edi	// odd
	mov $1, %edx

loop:
	call readi32
	jc exit

	test %eax, %edx
	jz add_even
	jnz add_odd
	
add_even:
	add %eax, %esi
	jmp loop

add_odd:
	add %eax, %edi
	jmp loop	

exit:
	mov %esi, %eax
	call writei32
	mov %edi, %eax
	call writei32

	call finish
