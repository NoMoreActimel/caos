    .global dot_product
dot_product:
    push %ebp
    mov %esp, %ebp
    push %ebx

    // 4(ebp) + 4(func call) + 4(ebx) + 4(n) + 
    // 4(double* x) + 4(double* y) + 4(double* res)

    movsd zero, %xmm0

    mov 12(%esp), %ecx
    // n in %ecx
    mov 24(%esp), %edx
    // res om %edx

    cmp $0, %ecx
    jz exit

    mov 16(%esp), %eax
    // x in %eax
    mov 20(%esp), %ebx
    // y in %ebx

    // %xmm0 - dotproduct
    // %xmm1 - x floats
    // %xmm2 - y floats

loop:
    cmp $4, %ecx
    jl last_operations

    movups (%eax), %xmm1
    movups (%ebx), %xmm2

    mulps %xmm2, %xmm1
    haddps %xmm1, %xmm1
    haddps %xmm1, %xmm1

    addss %xmm1, %xmm0

    add $16, %eax
    add $16, %ebx
    sub $4, %ecx
    jmp loop

last_operations:
    cmp $0, %ecx
    jz exit

    movsd zero, %xmm1
    movsd zero, %xmm2

    movss (%eax), %xmm1
    movss (%ebx), %xmm2

    mulss %xmm2, %xmm1
    addss %xmm1, %xmm0

    add $4, %eax
    add $4, %ebx
    dec %ecx
    jmp last_operations

exit:
    movss %xmm0, (%edx)
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret

    .data
zero:
    .double 0
one:
    .double 1