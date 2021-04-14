    global my_memcpy
    section .text

my_memcpy:
    cmp rdx, 0
    je exit
    sub rdx, 1
    mov rcx, 0
    jmp copy_loop

copy_loop:
    mov r8b, BYTE[rsi + rcx]
    mov BYTE[rdi + rcx], r8b
    cmp rdx, rcx
    je exit
    inc rcx
    jmp copy_loop

exit:
    ret
