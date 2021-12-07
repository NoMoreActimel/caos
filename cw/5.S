	.global delegate
delegate:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov 12(%esp), %ecx // n in ecx
	mov %ecx, %ebx // current size in ebx
	mov 16(%esp), %edx // func address in edx
	// from esp + 20 and further - n args
	// we will take the arg on esp + 4(n - 1) + 20,
	// push it one more time
	// for the (n - 1)-th arg current address 
	// is the same - esp + 4(n - 1) + 20, and so on

loop:
	cmp $0, %ebx
	jz function_call

	mov 16(%esp, %ecx, 4), %eax
	push %eax
	dec %ebx
	jmp loop

function_call:
	mov %ecx, %ebx // in case func chagnes ecx
	call *%edx

exit:
	shl $2, %ebx
	add %ebx, %esp

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret