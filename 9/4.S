    .global myexp
myexp:
    push %ebp
    mov %esp, %ebp

    // 4(ebp) + 4(func call) + 8(x) + 4(r*)

    movsd one, %xmm0
    // cur sum in %xmm0
    movsd one, %xmm1
    // prev sum in %xmm1
    movsd one, %xmm2
    // x^n in %xmm2    
    movsd 8(%esp), %xmm3
    // x in %xmm3
    movsd zero, %xmm4 
    // n in %xmm4
    movsd one, %xmm5
    // n! in %xmm5
    mov 16(%esp), %eax
    // r in %eax

loop:
    addsd one, %xmm4
    mulsd %xmm4, %xmm5
    mulsd %xmm3, %xmm2

    movsd %xmm2, %xmm6
    divsd %xmm5, %xmm6
    // x^n / n in %xmm6

    addsd %xmm6, %xmm0

    comisd %xmm1, %xmm0
    jz exit

    movsd %xmm0, %xmm1
    jmp loop

exit:
    movsd %xmm0, (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .double 0
one:
    .double 1