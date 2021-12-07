	.global free_mem, freelist
free_mem:
	push %ebp
	mov %esp, %ebp

	mov 8(%esp), %ecx // block body address in ecx

	cmp $0, %ecx
	jz exit

	mov freelist, %eax // prev head in eax
	mov -4(%ecx), %edx // block size-field address in edx
	mov %edx, freelist // now in freelist
	mov %eax, (%ecx) // next is prev head

exit:
	mov %ebp, %esp
	pop %ebp
	ret

	.data
freelist:
	.skip 4