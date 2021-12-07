	.global обработка

обработка:
	push %ebp
	mov %esp, %ebp
	push %ebx
	xor %edx, %edx // answer sum stored in edx

loop:
	test %ebx, %ebx
	jz exit

	xor %eax, %eax // current sum stored in eax

	add 4(%ebx, %esi, 4), %eax
	add 52(%ebx, %edi, 4), %eax

	mov (%ebx), %ebx

	cmp $0, %eax
	jge add_cur_sum
	inc %eax

add_cur_sum:
	sar $1, %eax
	add %eax, %edx
	jmp loop

exit:
	pop %ebx
	mov %ebp, %esp
	pop %ebp

	mov (%esp), %ecx
	sub $4, %esp
	mov %ecx, (%esp) // moved function call 1 pos further

	mov %edx, 4(%esp) // moved ans above the function call
	ret
