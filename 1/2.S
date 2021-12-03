	.global main
main:
	call readi32
	cmp $0, %eax
	jl prog_finish
	
loop_seq:
	call writei32
	dec %eax
	cmp $0, %eax
	jge loop_seq

prog_finish:
	call finish
