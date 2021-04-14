    global my_memset
    section .text

my_memset:
    ; void *memset(void *str, int c, size_t n)
    ;                    rdi,   sil,      rdx
    mov rax, rdi
    mov rcx, 0
    jmp fill_loop

fill_loop:
    cmp rdx, rcx
    je exit
    mov BYTE[rdi + rcx], sil
    inc rcx
    jmp fill_loop

exit:
    ret