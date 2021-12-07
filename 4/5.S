	.global qsort, sort_by_abs, cmp

cmp:
	push %ebp
	mov %esp, %ebp

	xor %eax, %eax
	xor %ecx, %ecx

	mov 8(%esp), %edx
	mov (%edx), %ax
	mov 12(%esp), %edx
	mov (%edx), %cx
	// first in ax, second in cx

	cmp %cx, %ax
	jz equal_abs

first_sign_check:
	cmp $-32768, %ax
	jz first_abs_greater

	cmp $0, %ax
	jge second_sign_check
	neg %ax

second_sign_check:
	cmp $-32768, %cx
	jz second_abs_greater

	cmp $0, %cx
	jge compare_abs
	neg %cx

compare_abs:
	cmp %cx, %ax
	jl second_abs_greater

first_abs_greater:
	mov $1, %eax
	jmp exit

second_abs_greater:
	mov $-1, %eax
	jmp exit

equal_abs:
	mov $0, %eax

exit:
	mov %ebp, %esp
	pop %ebp
	ret


sort_by_abs:
	push %ebp
	mov %esp, %ebp

	mov 8(%esp), %eax  // first address in eax
	mov 12(%esp), %ecx // size in ecx

	mov $cmp, %edx
	push %edx
	push $2
	push %ecx
	push %eax
	call qsort
	add $16, %esp

	mov %ebp, %esp
	pop %ebp
	ret