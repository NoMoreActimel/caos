#include <sys/syscall.h>

	.global main, alloc_mem, freelist
main:
	call alloc_mem
	call writei32
	call finish

alloc_mem:
	push %ebp
	mov %esp, %ebp
	push %ebx

	// ecx - current, ebx - prev

	mov $0, %ebx
	mov 8(%esp), %eax
	mov freelist, %ecx

		

loop:
	cmp %eax, (%ecx)
	jae delete_block

	mov %ecx, %ebx

	cmp $0, 4(%ecx)
	jz add_block

	mov 4(%ecx), %ecx
	jmp loop

delete_block:
	cmp $0, %ebx
	jz delete_head

	mov 4(%ecx), %edx
	mov %edx, 4(%ebx)
	mov 4(%ecx), %eax
	jmp exit

delete_head:
	mov 4(%ecx), %edx
	mov %edx, freelist
	mov 4(%ecx), %eax
	jmp exit

add_block:
	jmp actual_size
add_block2:
	mov (%ecx), %edx
	mov 
	call brk
	mov 

exit:
	pop %ebx
	mov %ebp, %esp
	pop %ebp


actual_size:
	cmp $0, %eax
	jz zero_size

	add $3, %eax
	shr $2, %eax
	shl $2, %eax
	jmp add_block2

zero_size:
	mov $4, %eax
	jmp add_block2

brk:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov 
	mov %eax, %ebx // actual size was stored at eax
	mov $SYS_brk, %eax
	int $0x80

	pop %ebx
	mov %ebp, %esp
	pop %ebp

	.data
freelist:
	.int 0
