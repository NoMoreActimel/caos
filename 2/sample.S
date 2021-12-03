	.global main

main:
	mov $stack, %eax
	mov %eax, head

	mov	head, %eax
	call writei32
	mov $stack, %eax
	call writei32
	call finish

	.data
stack:
	.skip 8000, 0
cur:
	.skip 4, 0
head:
	.skip 4, 0