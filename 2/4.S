	.global main, process

main:
	call persistent_stack
	call finish

persistent_stack:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov $stack, %eax
	mov %eax, end

loop:
  	call readi32
  	jc exit

  	cmp $0, %eax
  	js pop_i

  	cmp $101, %eax
  	jz print_stack

  	mov %eax, %ecx
  	call readi32
  	jmp push_i

push_i:
	mov end, %edx
  	mov %eax, (%edx)
  	mov %ecx, 4(%edx)
  	add $8, end
  	jmp loop

pop_i:
	mov end, %ecx
	cmp $stack, %ecx
	jz wrong_pop

	neg %eax
	dec %eax

	mov $stack, %edx
	mov (%edx, %eax, 8), %ecx
	mov 4(%edx, %eax, 8), %ebx

	cmp $-1, %ebx
	jz wrong_pop

	mov %ecx, %eax
	call writei32

	cmp $0, %ebx
	jz pop_last

	dec %ebx

	mov (%edx, %ebx, 8), %eax
	mov 4(%edx, %ebx, 8), %ecx
	jmp push_i

pop_last:
	mov $0, %eax
	mov $-1, %ecx
	jmp push_i

wrong_pop:
	mov $-1, %eax
	call writei32
	jmp loop

print_stack:
	movl $stack, cur

	movl $end, %eax
	call writei32

	movl $stack, %eax
	call writei32

	jmp loop
	jmp print_stack_loop

print_stack_loop:
	mov $3, %eax
	call writei32
	call nl

	mov cur, %ecx
	cmp $end, %ecx
	jz loop

	mov (cur), %eax
	call writei32

	add $4, cur
	mov (cur), %eax
	call writei32

	call nl

	add $8, cur
	jmp print_stack_loop


exit:
	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret


	.data
stack:
	.skip 8000, 0
cur:
	.skip 4, 0
end:
	.skip 4, 0
sz:
	.int 0