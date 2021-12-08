	.global aggregate
aggregate:
	push %ebp
	mov %esp, %ebp
	push %ebx
	push %esi
	push %edi

	mov 20(%esp), %edi // first address in edi
	mov 24(%esp), %esi // stats address in esi

 	cmp $0, %edi
 	jz zero_initialize

	mov $0, %eax
	mov $0, %ebx
	mov $-2147483648, %ecx
	mov $2147483647, %edx
	// eax - cnt, ebx - sum, ecx - max, edx - min

loop_start:
 	cmp $0, %edi
 	jz initialize

 	inc %eax
 	add (%edi), %ebx

 	cmp %ecx, (%edi)
 	jg new_max

 	cmp %edx, (%edi)
 	jl new_min

loop_end:
 	mov 4(%edi), %edi
 	jmp loop_start

new_max:
	mov (%edi), %ecx
	jmp loop_end

new_min:
	mov (%edi), %edx
	jmp loop_end


initialize:
	mov %edx, (%esi)
	mov %ecx, 4(%esi)

	mov %eax, %ecx
	mov %ebx, %eax
	mov %ecx, %ebx
	mov $0, %edx
	idiv %ebx
	mov %eax, 8(%esi)

	jmp exit

zero_initialize:
	mov $0, %eax
	mov %eax, (%esi)
	mov %eax, 4(%esi)
	mov %eax, 8(%esi)
	
	jmp exit


exit:
	pop %edi
	pop %esi
	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret
