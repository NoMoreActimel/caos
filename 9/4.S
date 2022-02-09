    .global myhypot
myhypot:
    push %ebp
    mov %esp, %ebp

    xorps %xmm0, %xmm0

    mov 8(%esp), %eax
    cmp $0, %eax

    // answer in %edx


    // 4(ebp) + 4(func call) + 4(n) + 4n(x) + 4n(y) + 4(res)
    movupd 8(%esp), %xmm0
    mov 24(%esp), %eax

    mulpd %xmm0, %xmm0
    haddpd %xmm0, %xmm0
    sqrtsd %xmm0, %xmm0

    movsd %xmm0, (%eax)

tail:



zero_exit:
    mov %eax, 12(%esp)

exit:
    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .double 0