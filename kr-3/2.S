    .global work_until_deadline
work_until_deadline:
    push %ebp
    mov %esp, %ebp
    push %ebx

    movss zero, %xmm0
    movss zero, %xmm1
    movss zero, %xmm2
    movss zero, %xmm3
    movss zero, %xmm4


    // 4(ebx) + 4(ebp) + 4(func call) + 4(uint64_t*) + 4(void*)
    mov 12(%esp), %ecx
    mov 16(%esp), %ebx

loop:
    movsd (%ecx), %xmm1
    cvtsd2si %xmm1, %xmm1

    call rdtsc
    movss %edx, %xmm3
    cvtsd2si %xmm3, %xmm0
    mov %eax, %xmm4
    cvtsd2si %xmm4, %xmm2

    movsd $2147483648, %xmm3
    pmulld %xmm3, %xmm0
    movsd $2, %xmm3
    pmulld %xmm3, %xmm0
 
    paddq %xmm2, %xmm0
    // rdtsc in xmm0

    cmpeq %xmm0, %xmm1
    jl loop_restart

    jmp exit

loop_restart:
    call *(%ebx)

exit:
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .float 0
