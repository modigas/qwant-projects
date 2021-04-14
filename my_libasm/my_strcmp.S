    global my_strcmp
    section .text

my_strcmp:
    mov rcx, 0
    jmp cmp_loop

cmp_loop:
    mov r8b, BYTE[rdi + rcx]
    mov r9b, BYTE[rsi + rcx]
    inc rcx
    cmp r8b, 0
    je end_case
    cmp r8b, r9b
    je cmp_loop
    jmp end_case

end_case:
    sub r8b, r9b
    movsx eax, r8b
    ret