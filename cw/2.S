	.equ SYS_EXIT, 1
	.equ SYS_READ, 3
	.equ SYS_WRITE, 4
	.equ STDIN_FILENO, 0
	.equ STDOUT_FILENO, 1
	.equ BUF_SIZE, 1

read_str:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov $SYS_READ, %eax
	mov $STDIN_FILENO, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	int $0x80

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret

print_str:
	push %ebp
	mov %esp, %ebp
	push %ebx

	mov $SYS_WRITE, %eax
	mov $STDOUT_FILENO, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	int $0x80

	pop %ebx
	mov %ebp, %esp
	pop %ebp
	ret

	.global main, cnt_lines, cnt_words, cnt_chars
main:
	mov $alphabet, %edi

first_line_prep:
	movb $1, %bl // add 1 to alphabet[c] for first string
	jmp loop

second_line_prep:
	cmpb $0, %bl
	jl compare_character_sets

	movb $-1, %bl
	jmp loop

loop:
	sub $BUF_SIZE, %esp	
	mov %esp, %esi
	push $BUF_SIZE
	push %esi
	call read_str
	add $8, %esp

	test %eax, %eax
	jz exit

	xor %eax, %eax
	movb (%esi), %al

	cmpb $32, %al
	jz loop

	cmpb $10, %al
	jz second_line_prep

	cmpb $97, %al
	jae prob_lowercase

	cmpb $65, %al
	jae prob_uppercase

other_symbols:
	addb %bl, (%edi, %eax, 1)
	jmp loop

prob_uppercase:
	cmpb $90, %al
	jbe uppercase
	jmp other_symbols

uppercase:
	addb %bl, (%edi, %eax, 1)
	addb $32, %al
	addb %bl, (%edi, %eax, 1)
	jmp loop

prob_lowercase:
	cmpb $122, %al
	jbe lowercase
	jmp other_symbols

lowercase:
	addb %bl, (%edi, %eax, 1)
	subb $32, %al
	addb %bl, (%edi, %eax, 1)
	jmp loop


compare_character_sets:
	mov $0, %eax

loop_compare:
	cmp $256, %eax
	jz print_yes

	movb (%edi, %eax, 1), %dl
	cmpb $0, %dl
	jnz print_no

	add $1, %eax
	jmp loop_compare

print_yes:
	push $4
	push $string_yes
	call print_str
	add $8, %esp
	jmp exit

print_no:
	push $3
	push $string_no
	call print_str
	add $8, %esp

exit:
	mov $SYS_EXIT, %eax
	mov $0, %ebx
	int $0x80

fail:
	mov $SYS_EXIT, %eax
	mov $1, %ebx
	int $0x80

	.data
alphabet:
	.skip 256, 0

string_no:
	.ascii "NO\n"

string_yes:
	.ascii "YES\n"