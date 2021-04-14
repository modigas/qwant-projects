    global my_index

    section .text
my_index:
    jmp compare

compare:
    cmp BYTE[rdi], sil
    je exit_success
    cmp BYTE[rdi], 0
    je exit_failure
    inc rdi
    jmp compare

exit_success:
    mov rax, rdi
    ret

exit_failure:
    mov rax, 0
    ret