.global qsort
    .global comp
    .global sort_by_abs
    //.global main
comp:
    push %ebp
    movl %esp, %ebp
    movl 8(%ebp), %ecx
    movl (%ecx), %eax
    cmpw $-32768, %ax
    jz a_min
    testw %ax, %ax
    jnl end_neg1
neg1:
    negw %ax
end_neg1:
    movl 12(%ebp), %ecx
    movw (%ecx), %dx
    cmpw $-32768, %dx
    jz le
    testw %dx, %dx
    jnl end_neg
neg:
    negl %edx
end_neg:
    cmpw %ax, %dx
    jl gre
    jg le
    jmp eq
eq:
    mov $0, %eax
    jmp end
gre:
    mov $1, %eax
    jmp end
le:
    mov $-1, %eax
    jmp end
a_min:
    movl 12(%ebp), %ecx
    movw (%ecx), %dx
    cmpw $-32768, %dx
    jz eq
    jmp gre
end:
    movl %ebp, %esp
    pop %ebp
    ret

sort_by_abs:
    push %ebp
    movl %esp, %ebp
    movl $comp, %eax
    push %eax
    movl $2, %eax
    push %eax
    push 12(%ebp)
    push 8(%ebp)
    call qsort
    movl %ebp, %esp
    pop %ebp
    ret
