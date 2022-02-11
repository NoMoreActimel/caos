    .text
    .global myexp
myexp:
    push %ebp
    mov %esp, %ebp

    movsd 8(%ebp), %xmm0
    movsd one, %xmm1
    movsd one, %xmm2
    movsd one, %xmm3
    movsd one, %xmm4
    
for:
    mulsd %xmm0, %xmm3
    divsd %xmm4, %xmm3
    movsd %xmm1, %xmm2
    addsd %xmm3, %xmm1
    addsd one, %xmm4
    comisd %xmm1, %xmm2
    jne for

    mov 16(%ebp), %eax
    movsd %xmm1, (%eax)

    mov %ebp, %esp
    pop %ebp
    ret

    .data
one:
    .double 1.0
