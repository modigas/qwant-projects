    global my_strncmp
    section .text

my_strncmp:
    mov rcx, 0
    sub rdx, 1
    jmp cmp_loop

cmp_loop:
    mov r8b, BYTE[rdi + rcx]
    mov r9b, BYTE[rsi + rcx]
    cmp rdx, rcx
    je end_case
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