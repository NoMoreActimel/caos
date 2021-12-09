	.global free_mem, freelist
free_mem:
	push %ebp
	mov %esp, %ebp

	mov 8(%esp), %ecx // block body address in ecx

	cmp $0, %ecx
	jz exit

	mov freelist, %eax // prev head in eax
	mov %eax, (%ecx) // next is prev head
	sub $4, %ecx
	mov %ecx, freelist // now in freelist

exit:
	mov %ebp, %esp
	pop %ebp
	ret

	.data
freelist:
	.skip 4