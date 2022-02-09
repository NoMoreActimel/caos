    .global myhypot
myhypot:
    push %ebp
    mov %esp, %ebp

    xorps %xmm0, %xmm0

    // 4(ebp) + 4(func call) + 8(double) + 8(double) + 4(double*)
    movupd 8(%esp), %xmm0
    mov 24(%esp), %eax

    mulpd %xmm0, %xmm0
    haddpd %xmm0, %xmm0
    sqrtsd %xmm0, %xmm0

    movsd %xmm0, (%eax)

    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .double 0