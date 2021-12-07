	.global obrabotka_call, p, обработка
obrabotka_call:
	push %ebp
	mov %esp, %ebp

	push %ebx
	push %esi
	push %edi

	mov p, %ebx
	mov $0, %esi
	mov $0, %edi

	call обработка
	pop %eax
	call writei32

	pop %edi
	pop %esi
	pop %ebx

	mov %ebp, %esp
	pop %ebp
	ret