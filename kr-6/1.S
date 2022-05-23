	.global run_on_stack
run_on_stack:
	push %ebp
	mov %esp, %ebp

	mov 16(%esp), %eax // stack_bottom
	mov 12(%esp), %ecx // arg
	mov 8(%esp), %edx // func

	sub $4, %eax
	mov %ecx, (%eax)
	// sub $4, %eax
	// mov %edx, (%eax)

	mov %eax, %esp
	call *%edx

	mov %ebp, %esp
	pop %ebp
	ret

// [ ... ebp run func arg st_b ]
//     ^

// [ ... st_b ebp run func arg st_b ]
//     ^
