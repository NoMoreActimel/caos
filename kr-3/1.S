    .global discrim
discrim:
    push %ebp
    mov %esp, %ebp

    movss zero, %xmm0
    movss zero, %xmm1
    movss zero, %xmm2

    // 4(ebp) + 4(func call) + 4(float) + 4(float) + 4(float) + 4(float*)
    movss 8(%esp), %xmm0
    movss 12(%esp), %xmm1
    movss 16(%esp), %xmm2
    mov 20(%esp), %eax

    mulss %xmm1, %xmm1
    mulss %xmm2, %xmm0
    mulss four, %xmm0
    subss %xmm0, %xmm1

    movss %xmm1, (%eax)

    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .float 0
four:
    .float 4